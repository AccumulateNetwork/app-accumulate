
#include <common/encoding/encoding.h>

//ENCODE_MARSHAL_BINARY_STATIC(Bytes64)
//ENCODE_UNMARSHAL_BINARY_STATIC(Bytes64)
ENCODE_EQUAL(Bytes64)
ENCODE_COPY(Bytes64)
ENCODE_BINARY_SIZE_STATIC(Bytes64)

Error Bytes64_valid(const Bytes* v) {
    if (!v) {
        return ErrorCode(ErrorParameterNil);
    }
    if (!v->buffer.ptr || v->buffer.size != 64) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    return ErrorCode(ErrorNone);
}

Error Bytes64_get(const struct Bytes64 *v, Bytes *out) {
    CHECK_ERROR(v)
    CHECK_ERROR(out)
    Error e = Bytes64_valid(&v->data);
    if ( e.code != ErrorNone ) {
        return e;
    }

    if (out->buffer.size < 64) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    int n = Bytes_copy(out, &v->data);
    if ( n != 64 ) {
        return ErrorCode(ErrorBadCopy);
    }
    return e;
}

Error Bytes64_set(struct Bytes64 *v, const Bytes *in) {
    CHECK_ERROR(v)
    CHECK_ERROR(in)
    Error e = Bytes64_valid(&v->data);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if (!in) {
        return ErrorCode(ErrorParameterNil);
    }
    if (in->buffer.size < 64) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    int n = Bytes_copy(&v->data, in);
    if ( n < 0 ) {
        return ErrorCode(n);
    }
    if ( n != 64 ) {
        return ErrorCode(ErrorBadCopy);
    }
    return e;
}

Bytes64 Bytes64_new(buffer_t *b, size_t n) {
    Bytes64 init = { { {0,0,0}}};

    if (b) {
        int sizeNeeded = (int)(64*n);
        if ( b->size - b->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = b->ptr;
        init.data.buffer.offset = b->offset;
        init.data.buffer.size = sizeNeeded;
        b->offset += sizeNeeded;
    }
    return init;
}

Bytes64 Bytes64_init(Bytes64_t *v) {
    buffer_t buffer = { v, 64, 0};
    return Bytes64_new(&buffer, 1);
}
