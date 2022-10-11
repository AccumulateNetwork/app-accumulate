#include "utils.h"

int readTokenRecipient(Unmarshaler *m, TokenRecipient *v) {
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

        b = unmarshalerReadUrl(m,&v->Url);
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

        b = unmarshalerReadBigInt(m,&v->Amount);
        CHECK_ERROR_CODE(b);
        n += b;
    }

    return n;
}
