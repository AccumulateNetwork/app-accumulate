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
#include "../sw.h"
#include "../globals.h"
#include "../crypto.h"
#include "../ui/display.h"
#include "../common/buffer.h"
#include "../transaction/types.h"
#include "../transaction/deserialize.h"

int handler_sign_tx(buffer_t *cdata, uint8_t chunk, bool more) {
    if (chunk == 0) {  // first APDU, parse BIP32 path
        explicit_bzero(&G_context, sizeof(G_context));
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

        static int a = 0;
        PRINTF("Checkpoint B:%d\n", a++);
        if (G_context.tx_info.raw_tx_len + cdata->size > MAX_TRANSACTION_LEN ||  //
            !buffer_move(cdata,
                         G_context.tx_info.raw_tx + G_context.tx_info.raw_tx_len,
                         cdata->size)) {
            return io_send_sw(SW_WRONG_TX_LENGTH);
        }

        G_context.tx_info.raw_tx_len += cdata->size;

        if (more) {
            // more APDUs to follow for transaction part
            return io_send_sw(SW_OK);
        }

        PRINTF("Checkpoint C: %d\n", G_context.tx_info.raw_tx_len);
        // we have received all the APDU's so let's parse and sign
        buffer_t buf = {.ptr = G_context.tx_info.raw_tx,
                        .size = G_context.tx_info.raw_tx_len,
                        .offset = 0};

        // now we need to go through the transaction and identify the header, body, and hash
        uint16_t len = 0;
        if (!buffer_read_u16(&buf, &len, BE)) {
            return io_send_sw(SW_TX_PARSING_FAIL);
        }

        // set the signer buffer
        buffer_t signerBuffer = {.ptr = buf.ptr + buf.offset, .size = len, .offset = 0};
        if (!buffer_seek_cur(&buf, len)) {
            return io_send_sw(SW_WRONG_TX_LENGTH);
        }

        // read the transaction length
        if (!buffer_read_u16(&buf, &len, BE)) {
            return io_send_sw(SW_TX_PARSING_FAIL);
        }

        // set the transaction buffer
        buffer_t transactionBuffer = {.ptr = buf.ptr + buf.offset, .size = len, .offset = 0};
        if (!buffer_seek_cur(&buf, len)) {
            return io_send_sw(SW_TX_PARSING_FAIL);
        }

        // temporary
        // read cheat code
        uint8_t hlen = 0;
        if (!buffer_read_u8(&buf, &hlen)) {
            return io_send_sw(0xB0EE);  // SW_TX_PARSING_FAIL);
        }

        if (hlen != sizeof(G_context.tx_info.m_hash)) {
            return io_send_sw(0xB000 + hlen);  // SW_TX_PARSING_FAIL);
        }

        // sign this
        if (!buffer_move(&buf, G_context.tx_info.m_hash, sizeof(G_context.tx_info.m_hash))) {
            return io_send_sw(0xB0F1);
        }
//
//        uint8_t arena[ARENA_SIZE] = {0};
//        buffer_t mempool = {arena, ARENA_SIZE, 0};
//        explicit_bzero(arena, ARENA_SIZE);
//        {
//            // we have signer buffer, now process it
//            Unmarshaler m = NewUnmarshaler(&signerBuffer, &mempool);
//            // int e = unmarshalerReadSignature(&m, &G_context.tx_info.signer);
//            int e = unmarshalerReadED25519Signature(&m, &G_context.tx_info.edSig);
//            if (IsError(ErrorCode(e))) {
//                return io_send_sw(SW_ENCODE_ERROR(ErrorCode(e)));
//            }
//        }
        {
            Transaction tx;
//            TransactionHeader header;
//            TokenRecipient tok;
//            SendTokens s = {.To_length = 1, .To = &tok, .Type = TransactionTypeSendTokens};
//
//            s.To_length = 1;
//            s.To = &tok;
//            tx.Body._SendTokens = &s;
//
//            buffer_seek_cur(&transactionBuffer, 1);
//            uint64_t size = 0;
//            int b = uvarint_read(transactionBuffer.ptr+transactionBuffer.offset,transactionBuffer.size - transactionBuffer.offset, &size);
//            buffer_seek_cur(&transactionBuffer, b);
//            buffer_seek_cur(&transactionBuffer, size);
//
//            buffer_seek_cur(&transactionBuffer, 1);
//            size = 0;
//            b = uvarint_read(transactionBuffer.ptr+transactionBuffer.offset,transactionBuffer.size - transactionBuffer.offset, &size);
//            buffer_seek_cur(&transactionBuffer, b);
//            buffer_seek_cur(&transactionBuffer, size);
            uint8_t arena[ARENA_SIZE] = {0};
            buffer_t mempool = {arena, ARENA_SIZE, 0};
            explicit_bzero(arena, ARENA_SIZE);

            Unmarshaler m = NewUnmarshaler(&transactionBuffer, &mempool);
            int e = unmarshalerReadTransaction(&m, &tx);
            if (IsError(ErrorCode(e))) {
                return io_send_sw(0xBAC0);
            }

            Signature signer;
            m = NewUnmarshaler(&signerBuffer, &mempool);
            e = unmarshalerReadSignature(&m, &signer);
            if (IsError(ErrorCode(e))) {
                return io_send_sw(0xBACC);
            }
        }
        io_send_sw(0xBAD0);

        G_context.state = STATE_PARSED;

        return 0;//ui_display_transaction(&G_context.tx_info.signer, &G_context.tx_info.transaction);
    }

    return 0;
}
