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

bool transaction_utils_check_encoding(const uint8_t *memo, uint64_t memo_len) {
    for (uint64_t i = 0; i < memo_len; i++) {
        if (memo[i] > 0x7F) {
            return false;
        }
    }

    return true;
}

bool transaction_utils_format_memo(const uint8_t *memo,
                                   uint64_t memo_len,
                                   char *dst,
                                   uint64_t dst_len) {
    if (memo_len > MAX_MEMO_LEN || dst_len < memo_len + 1) {
        return false;
    }

    memmove(dst, memo, memo_len);
    dst[memo_len] = '\0';

    return true;
}

#if 0
Error MerkleFieldHash(buffer_t **marshaledFieldBuffers, int numFieldBuffers) {
    uint8_t hash[32] = {0};
    Error e = ErrorCode(ErrorNone);
    for ( int i = 0; i < numFieldBuffers; i++ ) {
        e = sha256(marshaledFieldBuffers[i]->ptr+marshaledFieldBuffers[i]->offset,
               marshaledFieldBuffers[i]->size - marshaledFieldBuffers[i]->offset,
               hash, sizeof(hash));
        if (IsError(e)) {
            return e;
        }
    }
    bytes32 root = sha256(marshaledState);

    //compare the start of the proof and kick out if the hashes are not equal
    if ( root != start || entries.length > 64 ) {
        return false;
    }

    // Now apply all the path hashes to the root
    for (uint256 i = 0; i < entries.length; i++ )
    {
        if (lrBitfield & (1 << i) != 0) {
            // If this hash comes from the right, apply it that way
            root = sha256(abi.encodePacked(root,entries[i]));
            continue;
        }
        // If this hash comes from the left, apply it that way
        root = sha256(abi.encodePacked(entries[i],root));
    }


    return e;
}

#endif
int parse_transaction(uint8_t *raw_tx, uint16_t raw_tx_len, Signature *signer, Transaction *transaction, buffer_t *arena) {
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

        CHECK_ERROR_CODE(readSignature(&signerUnmarshaler, signer));
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
        CHECK_ERROR_CODE(readTransaction(&transactionUnmarshaler, transaction));
    }

        if (!buffer_seek_cur(&buf, len)) {
            PRINTF("cannot advance transaction buffer %d bytes\n", len);
            return ErrorBufferTooSmall;
        }
    PRINTF("checkpoint parse D\n");
//
//    uint8_t hlen = 0;
//    if (!buffer_read_u8(&buf, &hlen)) {
//        PRINTF("cannot read 8 byte transaction hash\n");
//        return ErrorBufferTooSmall;
//    }
//
//    if (hlen != hash_len) {
//        return ErrorBufferTooSmall;
//    }
//
//    PRINTF("checkpoint parse D\n");
//    // sign this
//    if (!buffer_move(&buf, hash, hash_len)) {
//        PRINTF("cannot read transaction hash\n");
//        return ErrorBufferTooSmall;
//    }

//    CHECK_ERROR_CODE(readTransaction(&transactionUnmarshaler, transaction));

//        return ErrorUnknown;
//    PRINTF("pre signer parse \n");
//    CHECK_ERROR_CODE(readSignature(&signerUnmarshaler, signer));
//    PRINTF("post signature parse \n");

    //    char outbuf[65] = {0};
//
//    format_hex(hash, 32, outbuf, sizeof(outbuf));
//    PRINTF("External HASH %s\n", outbuf);
//
//    format_hex(signer->_u->TransactionHash.data.buffer.ptr+signer->_u->TransactionHash.data.buffer.offset,
//               signer->_u->TransactionHash.data.buffer.size-signer->_u->TransactionHash.data.buffer.offset,
//               outbuf, sizeof(outbuf));
//    PRINTF("Transaction HASH %s\n", outbuf);
//
//    PRINTF("pre transaction parse A\n");

    //configure the arena
    int e = ErrorNone;


    PRINTF("DO TRANSACTION MAGIC\n");

    PRINTF("post transaction parse A\n");

    PRINTF("post transaction address %p\n", (void*)transaction->Body._SendTokens);


    return ErrorNone;
}

int readTransactionTypeHeader(Unmarshaler *m, TransactionType *type) {
    int n = 0;
    uint64_t field = 0;
    PRINTF("ENTERING READ TRANSACTION BODY\n");

    int b = unmarshalerReadField(m, &field);
    CHECK_ERROR_CODE(b);
    n += b;

    if ( field != 1 ) {
        return ErrorInvalidField;
    }

    PRINTF("DONE READ FIELD\n");

    b = unmarshalerReadUInt(m, &field);
    CHECK_ERROR_CODE(b);
    n += b;

    *type = (TransactionType)field;

    return n;
}

int readTransactionBody(Unmarshaler *m, TransactionBody *v) {
    int n = 0;
    TransactionType type = 0;
    PRINTF("ENTERING READ TRANSACTION BODY\n");

    int b = readTransactionTypeHeader(m, &type);
    CHECK_ERROR_CODE(b);

    n += b;

    PRINTF("READ  TRANSACTION BODY type %d\n", type);
    switch ( type ) {
        case TransactionTypeAddCredits:
            PRINTF("Allocate AddCredits\n");
            v->_AddCredits = (AddCredits *)unmarshalerAlloc(m, sizeof(AddCredits));
            CHECK_ERROR_INT(v->_AddCredits);

            b = readAddCredits(m, v->_AddCredits);
            CHECK_ERROR_CODE(b);

            n += b;
            //todo: compute body hash

            break;

        case TransactionTypeSendTokens:

            PRINTF("Allocate Send Tokens\n");
            v->_SendTokens = (SendTokens*)unmarshalerAlloc(m, sizeof(SendTokens));
            PRINTF("allocate SEND TOKENS %p size %d\n", v->_SendTokens, sizeof(SendTokens));
            CHECK_ERROR_INT(v->_SendTokens)

            PRINTF("Unmarshal Read Send Tokens\n");
            b = readSendTokens(m, v->_SendTokens);
            CHECK_ERROR_CODE(b);

            PRINTF("Unmarshal Read Send Tokens Complete\n");
            n += b;
            //todo: compute body hash

            break;

        default:
            n = ErrorNotImplemented;
    }

    return n;
}
