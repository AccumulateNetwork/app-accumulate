
#include <encoding/encoding.h>

ENCODE_BINARY_SIZE_STATIC(BigInt)
ENCODE_EQUAL(BigInt)
ENCODE_COPY(BigInt)

Error BigInt_valid(const Bytes *v) {
    CHECK_ERROR(v)
    if ( v->buffer.size != 32 && v->buffer.ptr != 0) {
        return ErrorCode(ErrorInvalidBigInt);
    }

    return ErrorCode(ErrorNone);
}

Error BigInt_get(const struct BigInt *s, uint256_t *v) {
    CHECK_ERROR(s)
    CHECK_ERROR(v)
    Error e = BigInt_valid(&s->data);
    if ( e.code != ErrorNone ) {
        return e;
    }

    frombytes256((uint8_t*)s->data.buffer.ptr+s->data.buffer.offset, s->data.buffer.size - s->data.buffer.offset, v);
    return ErrorCode(ErrorNone);
}

Error BigInt_set(struct BigInt *s, const uint256_t *v) {
    CHECK_ERROR(s)
    CHECK_ERROR(v)
    Error e = BigInt_valid(&s->data);
    if ( IsError(e) ) {
        return e;
    }

    uint8_t buffer[32] = {0};
    int n = tobytes256(v,buffer, sizeof(buffer));
    if ( n < 0 ) {
        return ErrorCode(ErrorInvalidBigInt);
    }
    if ( (int)s->data.buffer.size-(int)s->data.buffer.offset < n ) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    size_t offset = sizeof(buffer) - n;
    memmove(s->data.buffer.ptr+s->data.buffer.offset + offset, buffer, n);
    return ErrorCode(ErrorNone);
}

Error  BigInt_setFromString(struct BigInt *v, const char *in, size_t inLen) {
    CHECK_ERROR(in)

    uint256_t bigint;
    if ( fromstring256(in, inLen, &bigint) < 0 ) {
        return ErrorCode(ErrorInvalidBigInt);
    }

    return BigInt_set(v, &bigint);

}

Error  BigInt_setFromHex(struct BigInt *v, const char *in, size_t inLen) {
    CHECK_ERROR(in)

    uint256_t bigint;
    if ( fromhex256(in, inLen, &bigint) < 0 ) {
        return ErrorCode(ErrorInvalidBigInt);
    }

    return BigInt_set(v, &bigint);

}
BigInt BigInt_new(buffer_t *b) {
    BigInt init = { { {0,0,0}}};
    if (b) {
        int sizeNeeded = 32;
        if ( (int)(b->size - b->offset) < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = b->ptr;
        init.data.buffer.offset = b->offset;
        init.data.buffer.size = sizeNeeded;
        b->offset += sizeNeeded;
    }

    return init;
}

