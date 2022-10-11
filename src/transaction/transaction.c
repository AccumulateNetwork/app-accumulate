#include "utils.h"

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

            if ( !buffer_seek_cur(&m->buffer, size) ) {
                return ErrorBufferTooSmall;
            }
        }

        n += b;
    }

    return n;
}