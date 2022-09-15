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

cx_curve_t inferCurve(const uint32_t *bip32_path, uint8_t bip32_path_len) {
    if ( bip32_path_len < 3 ) {
        THROW(ErrorBufferTooSmall);
    }
    cx_curve_t curve = CX_CURVE_256K1;
    switch ( bip32_path[1] ) {
        case CoinTypeBtc:
        case CoinTypeEth:
            curve = CX_CURVE_256K1;
            break;
        case CoinTypeFct:
        case CoinTypeAcme:
            curve = CX_CURVE_Ed25519;
            break;
        default:
            THROW(ErrorInvalidEnum);
    }
    return curve;
}

int crypto_derive_private_key(cx_ecfp_private_key_t *private_key,
                              uint8_t chain_code[static 32],
                              const uint32_t *bip32_path,
                              uint8_t bip32_path_len) {
    uint8_t raw_private_key[32] = {0};

    BEGIN_TRY {
        TRY {
            // derive the seed with bip32_path using secp256k1
            os_perso_derive_node_bip32(CX_CURVE_256K1,
                                       bip32_path,
                                       bip32_path_len,
                                       raw_private_key,
                                       chain_code);

            // new ED25519 private_key from raw
            cx_ecfp_init_private_key(inferCurve(bip32_path, bip32_path_len),
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
                             uint8_t raw_public_key[static 65],//can be as large is 65 bytes
                             uint8_t *public_key_len,
                             bool compress) {
    // generate corresponding public key
    cx_ecfp_generate_pair(private_key->curve, public_key, private_key, 1);

    if ( !compress ) {
        memmove(raw_public_key, public_key->W, 65);
    } else {
        if (public_key->curve == CX_CURVE_256K1) {
            if (public_key->W[0] != 0x04) {
                return ErrorCode(ErrorBadKey);
            }
            raw_public_key[0] = (public_key->W[64] % 2 == 1) ? 0x03 : 0x02;
            memmove(raw_public_key + 1, public_key->W + 1, 32);  // copy x
            *public_key_len = 33;
        } else if (public_key->curve == CX_CURVE_Ed25519 && public_key->W[0] != 0xED) {
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


int crypto_sign_message() {
    cx_ecfp_private_key_t private_key = {0};
    uint8_t chain_code[32] = {0};
    uint32_t info = 0;
    int sig_len = 0;

    // derive private key according to BIP32 path
    crypto_derive_private_key(&private_key,
                              chain_code,
                              G_context.bip32_path,
                              G_context.bip32_path_len);

    BEGIN_TRY {
        TRY {
            sig_len = cx_ecdsa_sign(&private_key,
                                    CX_RND_RFC6979 | CX_LAST,
                                    CX_SHA256,
                                    G_context.tx_info.m_hash,
                                    sizeof(G_context.tx_info.m_hash),
                                    G_context.tx_info.signature,
                                    sizeof(G_context.tx_info.signature),
                                    &info);
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
