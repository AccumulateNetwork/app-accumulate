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

#include <stddef.h>  // size_t
#include <stdint.h>  // uint*_t
#include <string.h>  // memmove

#include "send_response.h"
#include "constants.h"
#include "globals.h"
#include "sw.h"
#include "common/buffer.h"
#include "crypto.h"

int helper_send_response_pubkey() {
    uint8_t resp[1 + 1 + PUBKEY_LEN + 1 + CHAINCODE_LEN + 1 + ADDRESS_NAME_LEN] = {0};
    size_t offset = 0;

    resp[offset++] = G_context.pk_info.public_key_length;
    memmove(resp + offset, G_context.pk_info.raw_public_key, G_context.pk_info.public_key_length);
    offset += G_context.pk_info.public_key_length;
    size_t len = strlen(G_context.pk_info.address_name);
    resp[offset++] = len;
    memmove(resp + offset, G_context.pk_info.address_name, len);
    offset += len;

    return io_send_response(&(const buffer_t){.ptr = resp, .size = offset, .offset = 0}, SW_OK);
}

int helper_send_response_sig(void) {
    uint8_t resp[1 + MAX_DER_SIG_LEN + 1 + 1 + 32] = {0};
    size_t offset = 0;

    resp[offset++] = G_context.tx_info.signature_len;
    memmove(resp + offset, G_context.tx_info.signature, G_context.tx_info.signature_len);
    offset += G_context.tx_info.signature_len;
    resp[offset++] = (uint8_t) G_context.tx_info.v;
    memmove( resp + offset, G_context.tx_info.metadataHash, 32);
    offset += 32;

    return io_send_response(&(const buffer_t){.ptr = resp, .size = offset, .offset = 0}, SW_OK);
}
