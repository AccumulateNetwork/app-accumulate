
#include <encoding/encoding.h>

ENCODE_MARSHAL_BINARY_STATIC(Bool)
ENCODE_UNMARSHAL_BINARY_STATIC(Bool)
ENCODE_EQUAL(Bool)
ENCODE_COPY(Bool)
ENCODE_BINARY_SIZE_STATIC(Bool)

Error Bool_valid(const Bytes *v) {
    if (!v) {
        return ErrorCode(ErrorParameterNil);
    }
    if (!v->buffer.ptr || v->buffer.size != 1) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    return ErrorCode(ErrorNone);
}

Error Bool_get(const struct Bool *v, Bytes *out) {
    CHECK_ERROR(v)
    CHECK_ERROR(out)
    Error e = Bool_valid(&v->data);
    if (e.code != ErrorNone) {
        return e;
    }

    if (out->buffer.size < 1) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    int n = Bytes_copy(out, &v->data);
    if (n != 1) {
        return ErrorCode(ErrorBadCopy);
    }
    return e;
}

Error Bool_set(struct Bool *v, const Bytes *in) {
    CHECK_ERROR(v)
    CHECK_ERROR(in)
    Error e = Bool_valid(&v->data);
    if (e.code != ErrorNone) {
        return e;
    }
    if (!in) {
        return ErrorCode(ErrorParameterNil);
    }
    if (in->buffer.size < 1) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    int n = Bytes_copy(&v->data, in);
    if (n < 0) {
        return ErrorCode(n);
    }
    if (n != 1) {
        return ErrorCode(ErrorBadCopy);
    }
    return e;
}

Bool Bool_new(buffer_t *b, size_t n) {
    Bool init = {{{0, 0, 0}}};

    if (b) {
        if (b->size - b->offset < n) {
            return init;
        }
        init.data.buffer.ptr = b->ptr + b->offset;
        init.data.buffer.offset = 0;
        init.data.buffer.size = n;
        b->offset += n;
    }
    return init;
}
