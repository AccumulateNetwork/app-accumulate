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

typedef struct MerkleState {
    buffer_t **hashlist[32];
    int hashlistlen;
    buffer_t **pending;
    int pendingLen;
    int pendingSize;
    int count;
} MerkleState;

Error MerkleState_DAGRoot(MerkleState *m, uint8_t mdroot[static 32]) {
    Error e = ErrorCode(ErrorNone);

    bool first = true;
    for (int i = 0; i < m->pendingLen; i++ ){ //_, v := range m.Pending {
        if (first) { // Pick up the first hash in m.MerkleState no matter what.
            first = false;
            memmove(mdroot, m->pending[i], 32);
            // = Hash(v).Copy() // If a nil is assigned over a nil, no harm no foul.  Fewer cases to test this way.
        } else if (m->pending[i] != 0 ) { // If MDRoot isn't nil and v isn't nil, combine them.
            // the pending hash is on the left, MDRoot candidate is on the right, for a new MDRoot
            uint8_t combine[64] = {0};
            memmove(combine, mdroot, 32);
            memmove(combine + 32, m->pending[i], 32 );
            e = sha256(combine, sizeof(combine), mdroot, 32);
            if (IsError(e) ) {
                return e;
            }
        }
    }
    return e;
}

Error MerkleState_PadPending(MerkleState *m) {
    int pendingLen = m->pendingLen;
    if ( pendingLen == 0 || m->pending[pendingLen-1] != 0) {
        //m.Pending = append(m.Pending, nil)
        m->pendingLen++;
    } else {
        return ErrorCode(ErrorInvalidHashParameters);
    }
    return ErrorCode(ErrorNone);
}

#if 0
void MerkleState_AddToMerkleTree(MerkleState *m, hash_ []byte) {
    //hash := Hash(hash_).Copy()
    //m.HashList = append(m.HashList, hash) // Add the new Hash to the Hash List
    m->count++;                             // Increment our total Hash Count
    MerkleState_PadPending(m);
    for (int i = 0; i < m->pendingLen; i++ ) {         // Adding the hash is like incrementing a variable
        if (m->pending[i] == 0) { //                     Look for an empty slot, and
           m->pending[i] = hash; //               And put the Hash there if one is found
           return;              //          Mission complete, so return
        }
        hash = Hash(v).Combine(Sha256, hash); // If this slot isn't empty, combine the hash with the slot
        m.Pending[i] = 0;                   //   and carry the result to the next (clearing this one)
        }




}

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
#include "common/format.h"
int parse_transaction(uint8_t *raw_tx, uint16_t raw_tx_len, Signature *signer, Transaction *transaction, buffer_t *arena,
                      uint8_t *hash, uint8_t hash_len) {
    Unmarshaler transactionMarshaler;
    Unmarshaler signerMarshaler;

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
    signerMarshaler.buffer.ptr = buf.ptr + buf.offset;
    signerMarshaler.buffer.size = len;
    signerMarshaler.buffer.offset = 0;
    if (!buffer_seek_cur(&buf, len))  {
        return ErrorBufferTooSmall;
    }

    // read the transaction length
    if (!buffer_read_u16(&buf, &len, BE)) {
        return ErrorBufferTooSmall;
    }

    PRINTF("checkpoint parse C\n");
    // set the transaction buffer
    transactionMarshaler.buffer.ptr = buf.ptr + buf.offset;
    transactionMarshaler.buffer.offset = 0;
    transactionMarshaler.buffer.size = len;

    if (!buffer_seek_cur(&buf, len)) {
        return ErrorBufferTooSmall;
    }

    PRINTF("checkpoint parse D\n");
    // temporary
    // read cheat code
    uint8_t hlen = 0;
    if (!buffer_read_u8(&buf, &hlen)) {
        return ErrorBufferTooSmall;
    }

    if (hlen != hash_len) {
        return ErrorBufferTooSmall;
    }

    PRINTF("checkpoint parse D\n");
    // sign this
    if (!buffer_move(&buf, hash, hash_len)) {
        return ErrorBufferTooSmall;
    }

    char outbuf[65] = {0};

    format_hex(hash, 32, outbuf, sizeof(outbuf));
    PRINTF("HASH %s\n", outbuf);

//return ErrorNone;

    PRINTF("pre transaction parse A\n");

    //configure the arena
    int e = ErrorNone;

    transactionMarshaler.mempool = arena;
    //
    //    uint64_t field = 0;
    //    unmarshalerReadField(&signerMarshaler, &field);
    //
    //    uint64_t size =0;
    //    int n = uvarint_read(signerMarshaler.buffer.ptr+signerMarshaler.buffer.offset,signerMarshaler.buffer.size-signerMarshaler.buffer.offset,&size);
    //    buffer_seek_cur(&signerMarshaler.buffer,n);
    //
    //    e = unmarshalerReadED25519Signature(&signerMarshaler, signer->_ED25519Signature);
    //    if (!IsError(ErrorCode(e))) {
    //        return e;
    //    }

    Unmarshaler *m = &transactionMarshaler;
    Transaction  *v = transaction;

    //signerMarshaler.mempool = &G_context.tx_info.arena;
    PRINTF("DO TRANSACTION MAGIC\n");
#if 1
    {
        PRINTF("READ TRANSACTION \n");
        int n = 0;
        int b = 0;
        uint64_t field = 0;

        PRINTF("READ TRANSACTION \n");

        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        CHECK_ERROR_CODE(b);

        buffer_seek_cur(&m->buffer, size);
        PRINTF("READING HEADER \n");
//        {
//                    n += b;
//                    Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
//                                      .mempool = m->mempool};
//                    b = unmarshalerReadTransactionHeader(&m2, &v->Header);
//                    if ( IsError(ErrorCode(b))) {
//                        return b;
//                    }
//                    buffer_seek_cur(&m->buffer, b);
//        }
        PRINTF("Done READ Header \n");


        n += b;
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;

        PRINTF("READ TRANSACTION BODY\n");

        size = 0;
        b = unmarshalerReadUInt(m,&size);
        CHECK_ERROR_CODE(b);

        n += b;

        {
            Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                              .buffer.size = size,
                              .buffer.offset = 0,
                              .mempool = m->mempool};
            b = readTransactionBody(&m3, &v->Body);
            CHECK_ERROR_CODE(b);
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }

#else
    e = unmarshalerReadTransaction(&transactionMarshaler, transaction);
    if (!IsError(ErrorCode(e))) {
        return e;
    }
#endif

    PRINTF("post transaction parse A\n");

    PRINTF("post transaction address %p", (void*)transaction->Body._SendTokens);


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
//#if _WANT_AddCredits_
//        case TransactionTypeAddCredits:
//            b = newAddCredits(m, v);
//            CHECK_ERROR_CODE(b);
//
//            b = unmarshalerReadAddCredits(m, v->_AddCredits);
//            CHECK_ERROR_CODE(b);
//
//            n += b;
//            break;
//#endif
#if _WANT_SendTokens_
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
            break;
#endif
        default:
            n = ErrorNotImplemented;
    };
    return n;
}

int readSendTokens(Unmarshaler *m, SendTokens *v) {
    int n = 0;
    int b = 0;
    uint64_t field = 0;
    v->Type = TransactionTypeSendTokens;

    while ( b != (int)(m->buffer.size - m->buffer.offset) ) {
        if ( m->buffer.offset == m->buffer.size ) {
            return n;
        }
        b = unmarshalerPeekField(m,&field);
        CHECK_ERROR_CODE(b);

        switch ( field ) {
            case 1: {
                if ( !buffer_seek_cur(&m->buffer,1) ) {
                    return ErrorBufferTooSmall;
                }
                n += 1;

                uint64_t type = 0;
                b = buffer_read_uvarint(&m->buffer, &type);
                CHECK_ERROR_CODE(b);

                if ( type != v->Type ) {
                    return ErrorInvalidObject;
                }
                n += b;

                break;
            }
            case 2: {
                if ( !buffer_seek_cur(&m->buffer,1) ) {
                    return ErrorBufferTooSmall;
                }
                n += 1;

                if ( !buffer_seek_cur(&m->buffer,32) ) {
                    return ErrorBufferTooSmall;
                }
                n += 32;
                break;
            }
            case 3: {
                if ( !buffer_seek_cur(&m->buffer,1) ) {
                    return ErrorBufferTooSmall;
                }
                n += 1;
                uint64_t size = 0;
                b = buffer_read_uvarint(&m->buffer, &size);
                CHECK_ERROR_CODE(b);
                n += b;

                //skip the buffer, don't need
                if ( !buffer_seek_cur(&m->buffer,size) ) {
                    return ErrorBufferTooSmall;
                }
                n += b;

                break;
            }
            case 4: {
                Unmarshaler m2 = {.buffer = m->buffer, .mempool = m->mempool};
                v->To_length = 0;
                while ( field == 4 ) {
                    b = unmarshalerReadField(&m2, &field);
                    CHECK_ERROR_CODE(b);

                    uint64_t size = 0;
                    b = unmarshalerReadUInt(&m2,&size);
                    CHECK_ERROR_CODE(b);
                    //skip the object
                    buffer_seek_cur(&m2.buffer, size);

                    v->To_length++;
                    field = 0;
                    unmarshalerPeekField(&m2, &field);
                }
                //now unmarshal for real...
                v->To = (TokenRecipient*)unmarshalerAlloc(m, v->To_length*sizeof(TokenRecipient));
                for ( size_t i = 0; i < v->To_length; ++i ) {
                    TokenRecipient *a = &v->To[i];

                    b = unmarshalerReadField(m, &field);
                    if (IsError(ErrorCode(b))) {
                        return b;
                    }
                    if (field != 4) {
                        return ErrorInvalidField;
                    }
                    n += b;
                    uint64_t size = 0;
                    b = unmarshalerReadUInt(m, &size);
                    CHECK_ERROR_CODE(b);

                    n += b;
                    {
                        Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                                          .buffer.size = size,
                                          .buffer.offset = 0,
                                          .mempool = m->mempool};
                        b = unmarshalerReadTokenRecipient(&m3, &v->To[i]);
                        CHECK_ERROR_CODE(b);
                    }
                    buffer_seek_cur(&m->buffer, b);
                    if ( b > (int)size ) {
                        return ErrorInvalidObject;
                    }

                    int skip = (int)size - b;
                    if ( !buffer_seek_cur(&m->buffer, skip) ) {
                        return ErrorInvalidObject;
                    }
                    b += (int)size-b;
                    n += b;
                }
                return n;
                //break;
            }
            default:
                return n;
        }
    }
    return n;
}