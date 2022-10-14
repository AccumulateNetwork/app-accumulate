#include "utils.h"

int readSendTokens(Unmarshaler *m, SendTokens *v) {
    int n = 0;
    uint64_t field = 0;
    v->Type = TransactionTypeSendTokens;

    memset(v->fieldsSet, 0, sizeof(v->fieldsSet));
    memset(v->extraData, 0, sizeof(v->extraData));

    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    int b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 1 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        v->extraData[field-1].buffer.offset = 0;
        v->extraData[field-1].buffer.size = 0;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;
        uint64_t type = 0;
        b = unmarshalerReadUInt(m,&type);
        CHECK_ERROR_CODE(b);
        n += b;

        if ( type != v->Type ) {
            return ErrorInvalidObject;
        }
        v->extraData[field-1].buffer.size += b;
        v->fieldsSet[field-1] = true;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 2 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        v->extraData[field-1].buffer.offset = 0;
        v->extraData[field-1].buffer.size = 0;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;

        b = unmarshalerReadBytes32(m,&v->Hash);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;
        v->fieldsSet[field-1] = true;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 3 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        v->extraData[field-1].buffer.offset = 0;
        v->extraData[field-1].buffer.size = 0;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;

        b = unmarshalerReadRawJson(m,&v->Meta);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;
        v->fieldsSet[field-1] = true;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 4 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        v->extraData[field-1].buffer.offset = 0;
        v->extraData[field-1].buffer.size = 0;
        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
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
        CHECK_ERROR_INT(v->To);
        for ( size_t i = 0; i < v->To_length; ++i ) {
            b = unmarshalerReadField(m, &field);
            CHECK_ERROR_CODE(b);
            n += b;
            if ( field != 4 ) {
                return ErrorInvalidField;
            }

            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            CHECK_ERROR_CODE(b);
            n += b;
            v->extraData[field-1].buffer.size += b;

            {
                Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                                  .buffer.size = size,
                                  .buffer.offset = 0,
                                  .mempool = m->mempool};
                b = readTokenRecipient(&m3, &v->To[i]);
                CHECK_ERROR_CODE(b);
            }
            buffer_seek_cur(&m->buffer, size);

            n += size;
            v->extraData[field-1].buffer.size += size;
        }

        v->fieldsSet[field-1] = true;
    }
    return n;
}