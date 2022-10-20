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
#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <string.h>   // memset, explicit_bzero

#include "os.h"
#include "cx.h"

#include "sign_tx.h"
#include "sw.h"
#include "globals.h"
#include "crypto.h"
#include "ui/display/display.h"
#include "common/buffer.h"
#include "transaction/types.h"
#include "transaction/utils.h"

int handler_sign_tx(buffer_t *cdata, uint8_t chunk, bool more) {

    if (chunk == 0) {  // first APDU, parse BIP32 path
        explicit_bzero(&G_context, sizeof(G_context));
        G_context.tx_info.arena.ptr = G_context.tx_info.memory;
        G_context.tx_info.arena.offset = 0;
        G_context.tx_info.arena.size = sizeof(G_context.tx_info.memory);

        G_context.req_type = CONFIRM_TRANSACTION;
        G_context.state = STATE_NONE;

        if (!buffer_read_u8(cdata, &G_context.bip32_path_len) ||
            !buffer_read_bip32_path(cdata,
                                    G_context.bip32_path,
                                    (size_t) G_context.bip32_path_len)) {
            return io_send_sw(SW_WRONG_DATA_LENGTH);
        }

        int raw_tx_len = cdata->size - cdata->offset;
        if (G_context.tx_info.raw_tx_len + raw_tx_len > MAX_TRANSACTION_LEN ||  //
            !buffer_move(cdata,
                         G_context.tx_info.raw_tx + G_context.tx_info.raw_tx_len,
                         raw_tx_len)) {
            return io_send_sw(SW_WRONG_TX_LENGTH);
        }
        PRINTF("Checkpoint A\n");
        G_context.tx_info.raw_tx_len = raw_tx_len;
        return io_send_sw(SW_OK);
    } else {  // parse transaction
        if (G_context.req_type != CONFIRM_TRANSACTION) {
            return io_send_sw(SW_BAD_STATE);
        }

        int raw_tx_len = cdata->size - cdata->offset;
        if (G_context.tx_info.raw_tx_len + raw_tx_len > MAX_TRANSACTION_LEN ||  //
            !buffer_move(cdata,
                         G_context.tx_info.raw_tx + G_context.tx_info.raw_tx_len,
                         raw_tx_len)) {
            return io_send_sw(SW_WRONG_TX_LENGTH);
        }

        G_context.tx_info.raw_tx_len += raw_tx_len;

        if (more) {
            // more APDUs to follow for transaction part
            return io_send_sw(SW_OK);
        }
PRINTF("checkpoint parse C\n");

        int e = parse_transaction(G_context.tx_info.raw_tx,
                                  G_context.tx_info.raw_tx_len,
                                  &G_context.tx_info.signer,
                                  &G_context.tx_info.transaction,
                                  &G_context.tx_info.arena);

        if (IsError(ErrorCode(e))) {
            return io_send_sw(SW_ENCODE_ERROR(ErrorCode(e)));
        }

        // Next do some sanity checks on the transaction to make sure it looks reasonable. These checks include
        // ensuring the correct public key is used, the initiator hash (if supplied) is correct and if not
        // supplied, will be computed and set, and the transaction hash (if supplied) is correct and if not
        // supplied, gets computed and set.

        //Step 1: check to make sure the signer used the correct public key
        {
            uint8_t raw_public_key[65] = {0};
            uint8_t public_key_length = sizeof(raw_public_key);
            cx_ecfp_private_key_t private_key = {0};
            cx_ecfp_public_key_t public_key = {0};

            // derive private key according to BIP32 path
            crypto_derive_private_key(&private_key,
                                      G_context.bip32_path,
                                      G_context.bip32_path_len);

            // generate corresponding public key
            Error e = crypto_init_public_key(&private_key, &public_key, raw_public_key,
                                             &public_key_length,
                                             G_context.bip32_path[1] != CoinTypeEth);
            // reset private key
            explicit_bzero(&private_key, sizeof(private_key));

            if (IsError(e)) {
                return io_send_sw(SW_ENCODE_ERROR(e));
            }

            //do a comparison of keys, set the initiator key if not present
            buffer_t pubKey = G_context.tx_info.signer._u->PublicKey.buffer;
            int keyLen = pubKey.size - pubKey.offset;

            PRINTF("\nLeylen %d\n", keyLen);
            PRINTF("PubKey TX: %.*H\n",keyLen, pubKey.ptr + pubKey.offset );
            PRINTF("PubKey Internal: %.*H\n",public_key_length, raw_public_key );
            //check to make sure the key's match and the key length is the expected length
            if ( public_key_length != (int)(keyLen) || !buffer_can_read(&pubKey, keyLen) ||
                 memcmp(pubKey.ptr+pubKey.offset, raw_public_key, keyLen) != 0 ) {
                //the key buffer is not set or not the right key, so give up
                return io_send_sw(SW_ENCODE_ERROR(ErrorCode(ErrorBadKey)));
            }
        }

        //Step 2: compute the initiator hash with given inputs, if signer supplied one, then compare it,
        //otherwise set it
        {

            G_context.tx_info.initiatorHash[0] = INITIATOR_FIELD_INDEX;
            e = initiatorHash(&G_context.tx_info.signer, &G_context.tx_info.initiatorHash[1]);
            if (IsError(ErrorCode(e))) {
                return io_send_sw(SW_ENCODE_ERROR(ErrorCode(e)));
            }
            // now set initiator hash if it isn't present in transaction header
            if (!buffer_can_read(&G_context.tx_info.transaction.Header.Initiator.data.buffer, 32)) {
                TransactionHeader *header = &G_context.tx_info.transaction.Header;
                header->Initiator.data.buffer =
                        (const buffer_t){.ptr = &G_context.tx_info.initiatorHash[1], .size = 32, .offset = 0};
                //required for transaction hash generation
                header->extraData[INITIATOR_FIELD_INDEX].buffer =
                        (const buffer_t){.ptr = G_context.tx_info.initiatorHash, .size = sizeof(G_context.tx_info.initiatorHash), .offset = 0};
            }
            // early check to see if our hashes match
            uint8_t initiator[32] = {0};
            Bytes hash =
                (const Bytes){.buffer.ptr = initiator, .buffer.size = sizeof(initiator), .buffer.offset = 0};
            Error err = Bytes32_get(&G_context.tx_info.transaction.Header.Initiator, &hash);
            if (IsError(err)) {
                return io_send_sw(SW_ENCODE_ERROR(err));
            }
            //initiator hash must match computed, otherwise fail.
            if (memcmp(initiator, &G_context.tx_info.initiatorHash[1], 32) != 0) {
                return io_send_sw(SW_ENCODE_ERROR(ErrorCode(ErrorInvalidHashParameters)));
            }
        }

        //Step 3: compute and compare (if supplied) the transaction  hash
        {
            Bytes hash = {.buffer.ptr = G_context.tx_info.m_hash,
                          .buffer.size = sizeof(G_context.tx_info.m_hash),
                          .buffer.offset = 0};

            // compute transaction hash
            e = transactionHash(&G_context.tx_info.transaction, G_context.tx_info.m_hash);
            if (IsError(ErrorCode(e))) {
                return io_send_sw(SW_ENCODE_ERROR(ErrorCode(e)));
            }

            if (!buffer_can_read(&G_context.tx_info.signer._u->TransactionHash.data.buffer, 32)) {
                // if we don't have a hash as part of the incoming payload, just use the one we computed.
                G_context.tx_info.signer._u->TransactionHash.data =
                    (const Bytes){.buffer.ptr = G_context.tx_info.m_hash,
                                  .buffer.size = sizeof(G_context.tx_info.m_hash),
                                  .buffer.offset = 0};
            }

            // early check to see if our hashes match
            uint8_t txHash[32] = {0};
            hash.buffer = (const buffer_t){.ptr = txHash, .size = sizeof(txHash), .offset = 0};
            Error err = Bytes32_get(&G_context.tx_info.signer._u->TransactionHash, &hash);
            if (IsError(err)) {
                return io_send_sw(SW_ENCODE_ERROR(err));
            }

            if (memcmp(txHash, G_context.tx_info.m_hash, 32) != 0) {
                return io_send_sw(SW_ENCODE_ERROR(ErrorCode(ErrorInvalidHashParameters)));
            }
        }

        G_context.state = STATE_PARSED;
        //Step 4: ask for user confirmation of transaction contents
        e = ui_display_transaction();
        if ( IsErrorCode(e)) {
            io_send_sw(SW_ENCODE_ERROR(ErrorCode(e)));
        }
    }
    return 0;
}
