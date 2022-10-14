#include "utils.h"

int readAddCredits(Unmarshaler *m, AddCredits *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    memset(v->fieldsSet, 0, sizeof(v->fieldsSet));
    memset(v->extraData, 0, sizeof(v->extraData));

    v->Type = TransactionTypeAddCredits;
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
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

        //ensure we are the correct union type
        uint64_t type = 0;
        b = unmarshalerReadUInt(m,&type);
        CHECK_ERROR_CODE(b);
        if ( type != v->Type ) {
            return ErrorInvalidObject;
        }
        n += b;
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

        b = unmarshalerReadUrl(m,&v->Recipient);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;
        v->fieldsSet[field-1] = true;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 3 )
    {
        v->extraData[field-1].buffer.ptr = m->buffer.ptr+m->buffer.offset;
        v->extraData[field-1].buffer.offset = 0;
        v->extraData[field-1].buffer.size = 0;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;

        b = unmarshalerReadBigInt(m,&v->Amount);
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
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;

        b = unmarshalerReadUVarInt(m,&v->Oracle);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field-1].buffer.size += b;
        v->fieldsSet[field-1] = true;
    }

    return n;
}
