#include "utils.h"

int readTransactionHeader(Unmarshaler *m, TransactionHeader *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    explicit_bzero(v->extraData, sizeof(v->extraData));

    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 1) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field - 1].buffer.size += b;

        b = unmarshalerReadUrl(m, &v->Principal);
        CHECK_ERROR_CODE(b);

        n += b;
        v->extraData[field - 1].buffer.size += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 2) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field - 1].buffer.size += b;

        b = unmarshalerReadBytes32(m, &v->Initiator);
        CHECK_ERROR_CODE(b);

        n += b;
        v->extraData[field - 1].buffer.size += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 3) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field - 1].buffer.size += b;

        b = unmarshalerReadString(m, &v->Memo);
        CHECK_ERROR_CODE(b);

        n += b;
        v->extraData[field - 1].buffer.size += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 4) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        v->extraData[field - 1].buffer.size += b;

        b = unmarshalerReadBytes(m, &v->Metadata);
        CHECK_ERROR_CODE(b);

        n += b;
        v->extraData[field - 1].buffer.size += b;
    }

    return n;
}
