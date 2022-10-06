#include "utils.h"

int readAddCredits(Unmarshaler *m, AddCredits *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    v->Type = TransactionTypeAddCredits;
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        //ensure we are the correct union type
        uint64_t type = 0;
        b = unmarshalerReadUInt(m,&type);
        CHECK_ERROR_CODE(b);
        if ( type != v->Type ) {
            return ErrorInvalidObject;
        }
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

        b = unmarshalerReadUrl(m,&v->Recipient);
        CHECK_ERROR_CODE(b);
        n += b;
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
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadBigInt(m,&v->Amount);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadUVarInt(m,&v->Oracle);
        CHECK_ERROR_CODE(b);
        n += b;
    }

    return n;
}
