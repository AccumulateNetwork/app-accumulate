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
#include <string.h>   // memmove
#include "utils.h"
#include "types.h"
#include "common/sha256.h"
#include "common/format.h"

#ifndef PRINTF
#define PRINTF
#endif


int parse_transaction(uint8_t *raw_tx, uint16_t raw_tx_len, Signature *signer, Transaction *transaction, buffer_t *arena,
                      uint8_t initiator[static 32], uint8_t txHash[static 32]) {
    PRINTF("checkpoint parse A\n");
    // we have received all the APDU's so let's parse and sign
    buffer_t buf = {.ptr = raw_tx,
                    .size = raw_tx_len,
                    .offset = 0};

    // now we need to go through the transaction and identify the header, body, and hash
    uint16_t len = 0;
    if (!buffer_read_u16(&buf, &len, BE)) {
        return ErrorBufferTooSmall;
    }

    PRINTF("checkpoint parse B\n");
    // set the signer buffer
    {
        Unmarshaler signerUnmarshaler = {.buffer.ptr = buf.ptr + buf.offset,
                                       .buffer.size = len,
                                       .buffer.offset = 0,
                                       .mempool = arena};
        PRINTF("pre signer parse \n");
        int e = readSignature(&signerUnmarshaler, signer);
        CHECK_ERROR_CODE(e);
        PRINTF("post signature parse \n");
    }

        //return ErrorInvalidObject;
    if (!buffer_seek_cur(&buf, len))  {
        PRINTF("signer buffer too small\n");
        return ErrorBufferTooSmall;
    }

    // read the transaction length
    if (!buffer_read_u16(&buf, &len, BE)) {
        PRINTF("cannot read 16 byte transaction length\n");
        return ErrorBufferTooSmall;
    }

    PRINTF("checkpoint parse C\n");
    // set the transaction buffer
    {
        Unmarshaler transactionUnmarshaler = {.buffer.ptr = buf.ptr + buf.offset,
                                            .buffer.size = len,
                                            .buffer.offset = 0,
                                            .mempool = arena};
        int e = readTransaction(&transactionUnmarshaler, transaction);
        CHECK_ERROR_CODE(e);
    }

    if (!buffer_seek_cur(&buf, len)) {
        PRINTF("cannot advance transaction buffer %d bytes\n", len);
        return ErrorBufferTooSmall;
    }

    return ErrorNone;
}

