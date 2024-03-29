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

#include "crypto.h"

#include <stdbool.h>  // bool
#include <stdint.h>   // uint*_t
#include <string.h>   // memset, explicit_bzero

#include "common/error.h"
#include "globals.h"

derivation_t inferCurve(const uint32_t *bip32_path, uint8_t bip32_path_len) {
    if (bip32_path_len < 3) {
        THROW(ErrorBufferTooSmall);
    }
    derivation_t derivation = {HDW_NORMAL, CX_CURVE_256K1, CX_CURVE_256K1};
    switch (bip32_path[1]) {
        case CoinTypeBtc:
        case CoinTypeEth:
            // do nothing
            break;
        case CoinTypeFct:
            // note FCT has a hybrid key generation sceheme.
            // It uses the normal secp256k1 derivation then generates an ed25519 key from that
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
    volatile uint8_t raw_private_key[64] = {0};
    volatile derivation_t curve = inferCurve(bip32_path, bip32_path_len);
    explicit_bzero(private_key, sizeof(cx_ecfp_private_key_t));

    cx_err_t err = os_derive_bip32_with_seed_no_throw(curve.mode,
                                                      curve.derivation_curve,
                                                      bip32_path,
                                                      bip32_path_len,
                                                      (uint8_t *) raw_private_key,
                                                      NULL,
                                                      NULL,
                                                      0);
    if (err != CX_OK) {
        explicit_bzero((void *) raw_private_key, sizeof(raw_private_key));
        return ErrorBadKey;
    }

    err = cx_ecfp_init_private_key_no_throw(curve.key_gen_curve,
                                            (uint8_t *) raw_private_key,
                                            32,
                                            private_key);
    explicit_bzero((void *) raw_private_key, sizeof(raw_private_key));
    if (err != CX_OK) {
        explicit_bzero((void *) private_key, sizeof(private_key));
        return ErrorBadKey;
    }

    return 0;
}

Error crypto_init_public_key(cx_ecfp_private_key_t *private_key,
                             cx_ecfp_public_key_t *public_key,
                             uint8_t *raw_public_key,  // can be as large is 65 bytes
                             uint8_t *public_key_len,
                             bool compress) {
    // generate corresponding public key
    cx_err_t err = cx_ecfp_generate_pair_no_throw(private_key->curve, public_key, private_key, 1);
    if (err != CX_OK) {
        return ErrorCode(ErrorBadKey);
    }

    // always compress ed25519
    if (!compress && public_key->curve != CX_CURVE_Ed25519) {
        if (*public_key_len < 65) {
            return ErrorCode(ErrorBufferTooSmall);
        }
        *public_key_len = 65;
        memmove(raw_public_key, public_key->W, *public_key_len);
    } else {
        if (public_key->curve == CX_CURVE_256K1) {
            if (*public_key_len < 33) {
                return ErrorCode(ErrorBufferTooSmall);
            }
            if (public_key->W[0] != 0x04) {
                return ErrorCode(ErrorBadKey);
            }
            raw_public_key[0] = (public_key->W[64] % 2 == 1) ? 0x03 : 0x02;
            memmove(raw_public_key + 1, public_key->W + 1, 32);
            *public_key_len = 33;
        } else if (public_key->curve == CX_CURVE_Ed25519 && public_key->W[0] != 0xED) {
            if (*public_key_len < 32) {
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
    size_t sig_len = sizeof(G_context.tx_info.signature);

    // derive private key according to BIP32 path
    int err =
        crypto_derive_private_key(&private_key, G_context.bip32_path, G_context.bip32_path_len);
    if (err != ErrorNone) {
        return err;
    }

    switch (private_key.curve) {
        case CX_CURVE_256K1:
            err = cx_ecdsa_sign_no_throw(&private_key,
                                         CX_RND_RFC6979 | CX_LAST,
                                         CX_SHA256,
                                         G_context.tx_info.m_hash,
                                         sizeof(G_context.tx_info.m_hash),
                                         G_context.tx_info.signature,
                                         &sig_len,
                                         &info);
            break;
        case CX_CURVE_Ed25519:
            sig_len = 64;
            err = cx_eddsa_sign_no_throw(&private_key,
                                         CX_SHA512,
                                         G_context.tx_info.m_hash,
                                         sizeof(G_context.tx_info.m_hash),
                                         G_context.tx_info.signature,
                                         sig_len);
            break;
        default:
            // defensive clearing of key
            PRINTF("Unknown curve in sign message %d\n", private_key.curve);
            explicit_bzero(&private_key, sizeof(private_key));
            return ErrorUnknown;
    }

    explicit_bzero(&private_key, sizeof(private_key));

    if (err != CX_OK) {
        return ErrorUnknown;
    }

    G_context.tx_info.signature_len = sig_len;
    G_context.tx_info.v = (uint8_t) (info & CX_ECCINFO_PARITY_ODD);

    return 0;
}

#ifndef _NR_cx_hash_ripemd160
cx_err_t cx_ripemd160_update(cx_ripemd160_t *ctx, const uint8_t *data, size_t len);
cx_err_t cx_ripemd160_final(cx_ripemd160_t *ctx, uint8_t *digest);
/** Missing in some SDKs, we implement it using the cxram section if needed. */
size_t cx_hash_ripemd160(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len) {
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
    // PRINT_STACK_POINTER();

    uint8_t buffer[32];
    cx_hash_sha256(in, inlen, buffer, 32);
    crypto_ripemd160(buffer, 32, out);
}
