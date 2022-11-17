#include "utils.h"
#include "common/sha256.h"
#include "common/format.h"

int getHeaderHash(TransactionHeader *v, uint8_t hash[static 32] ) {
    HashContext ctx;
    crypto_hash_init(&ctx);

    for ( uint8_t i = 0; i < sizeof(v->extraData)/sizeof(Bytes); i++ ) {

        if ( !v->extraData[i].buffer.ptr ) {
            continue;
        }
        crypto_hash_update(&ctx,
                           v->extraData[i].buffer.ptr+v->extraData[i].buffer.offset,
                           v->extraData[i].buffer.size - v->extraData[i].buffer.offset);
    }
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int getBodyHash(TransactionBody *v, uint8_t hash[static 32]) {
    int byteArrayLen = 0;
    Bytes *byteArray;
    switch(v->_u->Type) {
        case TransactionTypeAddCredits:{
            byteArray = v->_AddCredits->extraData;
            byteArrayLen = (int)sizeof(v->_AddCredits->extraData)/sizeof(Bytes);
        } break;
        case TransactionTypeSendTokens: {
            byteArray = v->_SendTokens->extraData;
            byteArrayLen = (int)sizeof(v->_SendTokens->extraData)/sizeof(Bytes);
        } break;
        case TransactionTypeUpdateKeyPage:
        case TransactionTypeUpdateKey:
        case TransactionTypeWriteData:
        case TransactionTypeWriteDataTo:
            return ErrorNotImplemented;
        default:
            return ErrorInvalidEnum;
    }

    HashContext ctx;
    crypto_hash_init(&ctx);
    for (int i = 0; i < byteArrayLen; i++) {
        if ( byteArray[i].buffer.ptr ) {
            buffer_t *buff = &byteArray[i].buffer;
            crypto_hash_update(&ctx,buff->ptr+buff->offset, buff->size-buff->offset);
        }
    }
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int transactionHash(Transaction *v, uint8_t hash[static 32]) {
    HashContext ctx;
    crypto_hash_init(&ctx);
    explicit_bzero(hash, 32);
    int e = getHeaderHash(&v->Header, hash);
    if (IsError(ErrorCode(e))) {
        return e;
    }
    crypto_hash_update(&ctx, hash, 32);
    explicit_bzero(hash, 32);
    getBodyHash(&v->Body, hash);
    crypto_hash_update(&ctx, hash, 32);
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int readTransaction(Unmarshaler *m, Transaction *v) {
    int n = 0;
    uint64_t field = 0;

    explicit_bzero(v->extraData, sizeof (v->extraData));
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    int b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 1 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field-1].buffer.size += b;
        n += b;

        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        CHECK_ERROR_CODE(b);
        v->extraData[field-1].buffer.size += b;
        n += b;
        {
            Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                              .buffer.size = size,
                              .buffer.offset = 0,
                              .mempool = m->mempool};
            b = readTransactionHeader(&m2, &v->Header);
            CHECK_ERROR_CODE(b);
        }
        buffer_seek_cur(&m->buffer, size);
        v->extraData[field-1].buffer.size += b;
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 2 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field-1].buffer.size += b;
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

            if ( !buffer_seek_cur(&m->buffer, size) ) {
                return ErrorBufferTooSmall;
            }
        }

        v->extraData[field-1].buffer.size += b;
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


            b = readAddCredits(m, v->_AddCredits);
            v->_AddCredits->extraData[0].buffer = bodyMark;
            CHECK_ERROR_CODE(b);

            n += b;
            //todo: compute body hash

            break;

        case TransactionTypeSendTokens:

            PRINTF("Allocate Send Tokens\n");
            v->_SendTokens = (SendTokens*)unmarshalerAlloc(m, sizeof(SendTokens));
            PRINTF("allocate SEND TOKENS %p size %d\n", v->_SendTokens, sizeof(SendTokens));
            CHECK_ERROR_INT(v->_SendTokens)
            //v->_SendTokens->fieldsSet[0] = true;


            PRINTF("Unmarshal Read Send Tokens\n");
            b = readSendTokens(m, v->_SendTokens);
            v->_SendTokens->extraData[0].buffer = bodyMark;
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
