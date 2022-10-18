#include "utils.h"
#include "common/sha256.h"

int getHeaderHash(TransactionHeader *v, uint8_t hash[static 32] ) {
    HashContext ctx;
    crypto_hash_init(&ctx);

    buffer_t buffers[4] = { v->Principal.data.buffer, v->Initiator.data.buffer, v->Memo.data.buffer, v->Metadata.buffer};

    for ( int i = 0; i < 4; i++ ) {
           crypto_hash_update(&ctx,
                           buffers[i].ptr+buffers[i].offset,
                           buffers[i].size - buffers[i].offset);
    }
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int getBodyHash(TransactionBody *v, uint8_t hash[static 32]) {

    HashContext ctx;
    crypto_hash_init(&ctx);
    uint8_t tt[10] = {0};
    int n = uvarint_write(tt,0,v->_u->Type);
    crypto_hash_update(&ctx, tt, n);
    switch(v->_u->Type) {
        case TransactionTypeAddCredits:{
            for (int i = 0; i < (int)sizeof(v->_AddCredits->fieldsSet); i++) {
                if ( v->_AddCredits->fieldsSet[i] ) {
                    buffer_t *buff = &v->_AddCredits->extraData[i].buffer;
                    crypto_hash_update(&ctx,buff->ptr+buff->offset, buff->size-buff->offset);
                }
            }
        } break;
        case TransactionTypeSendTokens: {
            for (int i = 0; i < (int)sizeof(v->_SendTokens->fieldsSet); i++) {
                if ( v->_SendTokens->fieldsSet[i] ) {
                    buffer_t *buff = &v->_SendTokens->extraData[i].buffer;
                    crypto_hash_update(&ctx,buff->ptr+buff->offset, buff->size-buff->offset);
                }
            }
            crypto_hash_final(&ctx, hash, 32);
        } break;
        case TransactionTypeUpdateKeyPage:
        case TransactionTypeUpdateKey:
        case TransactionTypeWriteData:
        case TransactionTypeWriteDataTo:
            return ErrorNotImplemented;
        default:
            return ErrorInvalidEnum;
    }
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int transactionHash(Transaction *v, uint8_t hash[static 32]) {
    HashContext ctx;
    crypto_hash_init(&ctx);
    getHeaderHash(&v->Header, hash);
    crypto_hash_update(&ctx, hash, 32);
    getBodyHash(&v->Body, hash);
    crypto_hash_update(&ctx, hash, 32);
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int readTransaction(Unmarshaler *m, Transaction *v) {
    int n = 0;
    uint64_t field = 0;

    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    int b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        CHECK_ERROR_CODE(b);
        n += b;
        {
            Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                              .buffer.size = size,
                              .buffer.offset = 0,
                              .mempool = m->mempool};
            b = readTransactionHeader(&m2, &v->Header);
            CHECK_ERROR_CODE(b);
        }
        v->HeaderBuffer.ptr = m->buffer.ptr + m->buffer.offset;
        v->HeaderBuffer.offset = 0;
        v->HeaderBuffer.size = size;
        buffer_seek_cur(&m->buffer, size);

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        {
            uint64_t size = 0;
            b = unmarshalerReadUInt(m, &size);
            CHECK_ERROR_CODE(b);
            n += b;

            Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                              .buffer.size = size,
                              .buffer.offset = 0,
                              .mempool = m->mempool};
            b = readTransactionBody(&m2, &v->Body);
            CHECK_ERROR_CODE(b);

            v->BodyBuffer.ptr = m->buffer.ptr + m->buffer.offset;
            v->BodyBuffer.offset = 0;
            v->BodyBuffer.size = size;
            if ( !buffer_seek_cur(&m->buffer, size) ) {
                return ErrorBufferTooSmall;
            }
        }

        n += b;
    }

    return n;
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

    buffer_t bodyMark = { m->buffer.ptr+m->buffer.offset, 0,0};
    int b = readTransactionTypeHeader(m, &type);
    CHECK_ERROR_CODE(b);

    n += b;
    bodyMark.size += b;

    PRINTF("READ  TRANSACTION BODY type %d\n", type);
    switch ( type ) {
        case TransactionTypeAddCredits:
            PRINTF("Allocate AddCredits\n");
            v->_AddCredits = (AddCredits *)unmarshalerAlloc(m, sizeof(AddCredits));
            CHECK_ERROR_INT(v->_AddCredits);

            v->_AddCredits->fieldsSet[0] = true;
            v->_AddCredits->extraData[0].buffer = bodyMark;

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
            v->_SendTokens->fieldsSet[0] = true;
            v->_SendTokens->extraData[0].buffer = bodyMark;

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
