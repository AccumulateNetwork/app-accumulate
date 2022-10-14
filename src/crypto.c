/*****************************************************************************
 *   Accumulate Ledger Wallet
 *   (c) 2022 DefiDevs, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#include <stdint.h>   // uint*_t
#include <string.h>   // memset, explicit_bzero
#include <stdbool.h>  // bool
#include "common/error.h"
#include "crypto.h"
#include "cx.h"
#include "memory.h"
#include "globals.h"

typedef struct  {
    unsigned int mode;
    cx_curve_t derivation_curve;
    cx_curve_t key_gen_curve;
} derivation_t;

derivation_t inferCurve(const uint32_t *bip32_path, uint8_t bip32_path_len) {
    if ( bip32_path_len < 3 ) {
        THROW(ErrorBufferTooSmall);
    }
    derivation_t derivation = { HDW_NORMAL, CX_CURVE_256K1, CX_CURVE_256K1};
    switch ( bip32_path[1] ) {
        case CoinTypeBtc:
        case CoinTypeEth:
            //do nothing
            break;
        case CoinTypeFct:
            derivation.key_gen_curve = CX_CURVE_Ed25519;
            break;
        case CoinTypeAcme:
            derivation.mode = HDW_ED25519_SLIP10;
            derivation.key_gen_curve = derivation.derivation_curve = CX_CURVE_Ed25519;
            break;
        default:
            THROW(ErrorInvalidEnum);
    }
    return derivation;
}

int crypto_derive_private_key(cx_ecfp_private_key_t *private_key,
                              const uint32_t *bip32_path,
                              uint8_t bip32_path_len) {
    uint8_t raw_private_key[32] = {0};

    BEGIN_TRY {
        TRY {
            derivation_t curve = inferCurve(bip32_path, bip32_path_len);
            os_perso_derive_node_with_seed_key(
                curve.mode,
                curve.derivation_curve,
                bip32_path,
                bip32_path_len,
                raw_private_key,
                NULL,
                NULL,
                0);

            cx_ecfp_init_private_key(curve.key_gen_curve,
                                     raw_private_key,
                                     sizeof(raw_private_key),
                                     private_key);
        }
        CATCH_OTHER(e) {
            THROW(e);
        }
        FINALLY {
            explicit_bzero(&raw_private_key, sizeof(raw_private_key));
        }
    }
    END_TRY;

    return 0;
}

Error crypto_init_public_key(cx_ecfp_private_key_t *private_key,
                             cx_ecfp_public_key_t *public_key,
                             uint8_t *raw_public_key,//can be as large is 65 bytes
                             uint8_t *public_key_len,
                             bool compress) {
    // generate corresponding public key
    cx_ecfp_generate_pair(private_key->curve, public_key, private_key, 1);

    //always compress ed25519
    if ( !compress && public_key->curve != CX_CURVE_Ed25519) {
        if (*public_key_len < 65 ) {
            return ErrorCode(ErrorBufferTooSmall);
        }
        *public_key_len = 65;
        memmove(raw_public_key, public_key->W, *public_key_len);
    } else {
        if (public_key->curve == CX_CURVE_256K1) {
            if ( *public_key_len < 33 ) {
                return ErrorCode(ErrorBufferTooSmall);
            }
            if (public_key->W[0] != 0x04) {
                return ErrorCode(ErrorBadKey);
            }
            raw_public_key[0] = (public_key->W[64] % 2 == 1) ? 0x03 : 0x02;
            memmove(raw_public_key + 1, public_key->W + 1, 32);
            *public_key_len = 33;
        } else if (public_key->curve == CX_CURVE_Ed25519 && public_key->W[0] != 0xED) {
            if ( *public_key_len < 32 ) {
                return ErrorCode(ErrorBufferTooSmall);
            }
            for (uint8_t i = 0; i < *public_key_len; i++) {
                raw_public_key[i] = public_key->W[64 - i];
            }
            if ((public_key->W[32] & 1) != 0) {
                raw_public_key[31] |= 0x80;
            }
            *public_key_len = 32;
        } else {
            return ErrorCode(ErrorInvalidObject);
        }
    }

    return ErrorCode(ErrorNone);
}

int crypto_sign_message(void) {
    cx_ecfp_private_key_t private_key = {0};
    uint32_t info = 0;
    int sig_len = 0;

    // derive private key according to BIP32 path
    crypto_derive_private_key(&private_key,
                              G_context.bip32_path,
                              G_context.bip32_path_len);

    BEGIN_TRY {
        TRY {
            switch (private_key.curve) {
            case CX_CURVE_256K1:
               sig_len = cx_ecdsa_sign(&private_key,
                                        CX_RND_RFC6979 | CX_LAST,
                                        CX_SHA256,
                                        G_context.tx_info.m_hash,
                                        sizeof(G_context.tx_info.m_hash),
                                        G_context.tx_info.signature,
                                        sizeof(G_context.tx_info.signature),
                                        &info);
                break;
            case CX_CURVE_Ed25519:
                sig_len = cx_eddsa_sign(&private_key,
                                        CX_LAST, CX_SHA512,
                                        G_context.tx_info.m_hash,
                                        sizeof(G_context.tx_info.m_hash),
                                        NULL, 0,
                                        G_context.tx_info.signature,
                                        sizeof(G_context.tx_info.signature),
                                        NULL);
                break;
            default:
                THROW(ErrorInvalidEnum);
            }
            PRINTF("Signature: %.*H\n", sig_len, G_context.tx_info.signature);
        }
        CATCH_OTHER(e) {
            THROW(e);
        }
        FINALLY {
            explicit_bzero(&private_key, sizeof(private_key));
        }
    }
    END_TRY;

    if (sig_len < 0) {
        return -1;
    }

    G_context.tx_info.signature_len = sig_len;
    G_context.tx_info.v = (uint8_t)(info & CX_ECCINFO_PARITY_ODD);

    return 0;
}

#ifndef _NR_cx_hash_ripemd160
/** Missing in some SDKs, we implement it using the cxram section if needed. */
size_t cx_hash_ripemd160(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len) {
    //PRINT_STACK_POINTER();

    if (out_len < CX_RIPEMD160_SIZE) {
        return 0;
    }
    cx_ripemd160_t cx;
    cx_ripemd160_init_no_throw(&cx);
    cx_ripemd160_update(&cx, in, in_len);
    cx_ripemd160_final(&cx, out);
    explicit_bzero(&cx, sizeof(cx_ripemd160_t));
    return CX_RIPEMD160_SIZE;
}
#endif  // _NR_cx_hash_ripemd160

void crypto_ripemd160(const uint8_t *in, uint16_t inlen, uint8_t out[static 20]) {
    cx_hash_ripemd160(in, inlen, out, 20);
}

void crypto_hash160(const uint8_t *in, uint16_t inlen, uint8_t out[static 20]) {
    //PRINT_STACK_POINTER();

    uint8_t buffer[32];
    cx_hash_sha256(in, inlen, buffer, 32);
    crypto_ripemd160(buffer, 32, out);
}

