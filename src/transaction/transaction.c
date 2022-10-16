#include "utils.h"
#include "common/sha256.h"

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

//    hasher, ok := t.Body.(interface{ GetHash() []byte })
//    if ok {
//        return hasher.GetHash()
//    }
//
//    data, err := t.Body.MarshalBinary()
//    if err != nil {
//        // TransactionPayload.MarshalBinary should never return an error, but
//        // better a panic then a silently ignored error.
//        panic(err)
//    }
//
//    hash := sha256.Sum256(data)
    return ErrorNone;
}

int transactionHash(Transaction *v, uint8_t hash[static 32]) {
#if 0
    switch( v->Header)
    v->BodyBuffer
    // Marshal the header
//    header, err := t.Header.MarshalBinary()
//    if err != nil {
//        // TransactionHeader.MarshalBinary will never return an error, but better safe than sorry.
//        panic(err)
//    }
//    headerHash := sha256.Sum256(header)
//
//    // Calculate the hash
//    sha := sha256.New()
//    sha.Write(headerHash[:])
//    sha.Write(t.getBodyHash())
//    t.hash = sha.Sum(nil)
#endif
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