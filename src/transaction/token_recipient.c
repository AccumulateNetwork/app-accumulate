#include "utils.h"

int readTokenRecipient(Unmarshaler *m, TokenRecipient *v) {
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    memset(v->fieldsSet, 0, sizeof(v->fieldsSet));
    memset(v->extraData, 0, sizeof(v->extraData));

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

        b = unmarshalerReadUrl(m,&v->Url);
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

    if ( field == 2 )
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

    return n;
}
