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

#include "get_public_key.h"

#include <common/buffer.h>
#include <common/error.h>
#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdint.h>   // uint*_t
#include <string.h>   // memset, explicit_bzero

#include "../crypto.h"
#include "../globals.h"
#include "../helper/send_response.h"
#include "../io.h"
#include "../sw.h"
#include "../types.h"
#include "../ui/display/display.h"
#include "address.h"
#include "cx.h"
#include "os.h"

int handler_get_public_key(buffer_t *cdata, bool display) {
    explicit_bzero(&G_context, sizeof(G_context));
    G_context.req_type = CONFIRM_ADDRESS;
    G_context.state = STATE_NONE;
    G_context.pk_info.public_key_length = sizeof(G_context.pk_info.raw_public_key);

    if (!buffer_read_u8(cdata, &G_context.bip32_path_len) ||
        !buffer_read_bip32_path(cdata, G_context.bip32_path, (size_t) G_context.bip32_path_len)) {
        return io_send_sw(SW_WRONG_DATA_LENGTH);
    }

    uint8_t addressNameLen = 0;
    char addressName[64] = {0};
    if (buffer_read_u8(cdata, &addressNameLen)) {
        if (addressNameLen > sizeof(addressName)) {
            return io_send_sw(SW_WRONG_DATA_LENGTH);
        }
        if (!buffer_move(cdata, (uint8_t *) addressName, addressNameLen)) {
            return io_send_sw(SW_ENCODE_ERROR(ErrorCode(ErrorInvalidString)));
        }
    }

    cx_ecfp_private_key_t private_key = {0};
    cx_ecfp_public_key_t public_key = {0};

    // derive private key according to BIP32 path
    crypto_derive_private_key(&private_key, G_context.bip32_path, G_context.bip32_path_len);

    // generate corresponding public key
    Error e = crypto_init_public_key(&private_key,
                                     &public_key,
                                     G_context.pk_info.raw_public_key,
                                     &G_context.pk_info.public_key_length,
                                     G_context.bip32_path[1] != CoinTypeEth);
    // reset private key
    explicit_bzero(&private_key, sizeof(private_key));

    if (IsError(e)) {
        return io_send_sw(SW_ENCODE_ERROR(e));
    }

    e = lite_address_from_pubkey(G_context.bip32_path[1], &G_context.pk_info);
    if (IsError(e)) {
        return io_send_sw(SW_ENCODE_ERROR(e));
    }

    // if we have an address name supplied to us override the name we derived.
    if (addressNameLen > 0) {
        strncpy(G_context.pk_info.address_name,
                addressName,
                sizeof(G_context.pk_info.address_name) - 1);
    }

    if (display) {
        return ui_display_address();
    }

    return helper_send_response_pubkey();
}
