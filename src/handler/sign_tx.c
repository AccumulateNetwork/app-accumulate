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
#include "../transaction/utils.h"

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

        PRINTF("checkpoint parse C\n");
        Signature signer;
#if 1
        G_context.tx_info.arena.ptr = G_context.tx_info.raw_tx + G_context.tx_info.raw_tx_len;
        G_context.tx_info.arena.offset = 0;
        G_context.tx_info.arena.size = sizeof(G_context.tx_info.raw_tx) - G_context.tx_info.raw_tx_len;

        //signer._ED25519Signature = &G_context.tx_info.edsig;
        int e = parse_transaction(G_context.tx_info.raw_tx, G_context.tx_info.raw_tx_len,
                          &signer, &G_context.tx_info.transaction, &G_context.tx_info.arena,
                                  G_context.tx_info.m_hash, sizeof(G_context.tx_info.m_hash));
        if ( IsError(ErrorCode(e))) {
            return io_send_sw(SW_ENCODE_ERROR(ErrorCode(e)));
        }
        PRINTF("checkpoint post parse C\n");
#endif
        G_context.state = STATE_PARSED;

        return ui_display_transaction(&signer, &G_context.tx_info.transaction);
    }

    return 0;
}
