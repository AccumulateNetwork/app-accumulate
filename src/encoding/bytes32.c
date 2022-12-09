
#include <encoding/encoding.h>

ENCODE_EQUAL(Bytes32)
ENCODE_COPY(Bytes32)
ENCODE_BINARY_SIZE_STATIC(Bytes32)

Error Bytes32_valid(const struct Bytes *v) {
    if (!v) {
        return ErrorCode(ErrorParameterNil);
    }
    if (!v->buffer.ptr || v->buffer.size - v->buffer.offset != 32) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    return ErrorCode(ErrorNone);
}

Error Bytes32_get(const struct Bytes32 *v, Bytes *out) {
    CHECK_ERROR(v)
    Error e = Bytes32_valid(&v->data);
    if (e.code != ErrorNone) {
        return e;
    }
    if (!out) {
        return ErrorCode(ErrorParameterNil);
    }
    if (out->buffer.size < 32) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    int n = Bytes_copy(out, &v->data);
    if (n != 32) {
        return ErrorCode(ErrorBadCopy);
    }
    return e;
}

Error Bytes32_set(Bytes32 *v, const Bytes *in) {
    CHECK_ERROR(v)
    Error e = Bytes32_valid(&v->data);
    if (e.code != ErrorNone) {
        return e;
    }
    if (!in) {
        return ErrorCode(ErrorParameterNil);
    }
    if (in->buffer.size < 32) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    int n = Bytes_copy(&v->data, in);
    if (n < 0) {
        return ErrorCode(n);
    }
    if (n != 32) {
        return ErrorCode(ErrorBadCopy);
    }
    return e;
}

Bytes32 Bytes32_new(buffer_t *b, size_t n) {
    Bytes32 init = {{0, 0, 0}};

    if (b) {
        unsigned int sizeNeeded = 32 * n;
        if (b->size - b->offset < sizeNeeded) {
            return init;
        }
        init.data.buffer.ptr = b->ptr;
        init.data.buffer.offset = b->offset;
        init.data.buffer.size = sizeNeeded;
        b->offset += sizeNeeded;
    }
    return init;
}

Bytes32 Bytes32_init(Bytes32_t *v) {
    buffer_t buffer = {v->x, 32, 0};
    return Bytes32_new(&buffer, 1);
}
