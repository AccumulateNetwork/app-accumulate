#include "utils.h"


// UnmarshalBinary unmarshals the transaction header from bytes as a unsigned varint.
int readTransactionHeader(Unmarshaler *m, TransactionHeader *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;


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

        b = unmarshalerReadUrl(m,&v->Principal);
        CHECK_ERROR_CODE(b);
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

        b = unmarshalerReadBytes32(m,&v->Initiator);
        CHECK_ERROR_CODE(b);
        n += b;
    }

    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadString(m,&v->Memo);
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

        b = unmarshalerReadBytes(m,&v->Metadata);
        CHECK_ERROR_CODE(b);
        n += b;
    }

    return n;
}

