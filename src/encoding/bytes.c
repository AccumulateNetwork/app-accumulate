
#include <encoding/encoding.h>
#include <encoding/marshaler.h>

int Bytes_binarySizeStatic(const struct Bytes *self) {
    if (!self) {
        return 0;
    }
    return (int)self->buffer.size - (int)self->buffer.offset;
}

int Bytes_binarySizeDynamic(const struct Bytes *self) {
    if (!self) {
        return 0;
    }
    int n = varint_size(self->buffer.size);
    return n + (int)self->buffer.size - (int)self->buffer.offset;
}

int Bytes_binarySize(const Bytes *v) {
    return Bytes_binarySizeDynamic(v);
}

///alloc populate buffer for a given amount from mempool
Error alloc(buffer_t *out, size_t amount, buffer_t *mempool) {
    UNUSED(out);
    if ( !buffer_can_read(mempool, amount ) ) {
        return ErrorCode(ErrorParameterInsufficientData);
    }
    mempool->offset += amount;
    return ErrorCode(ErrorNone);
}

bool Bytes_equal(const Bytes *b1,const Bytes *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }
    if ( b1->buffer.size != b2->buffer.size ) {
        return false;
    }
    return memcmp(b1->buffer.ptr+b1->buffer.offset, b2->buffer.ptr+b2->buffer.offset, b1->buffer.size)==0;
}

int Bytes_copy(Bytes *dst, const Bytes *src) {
    if ( !dst || !src ) {
        return ErrorParameterNil;
    }
    if ( dst->buffer.size < src->buffer.size ) {
        return ErrorBufferTooSmall;
    }

    memmove((uint8_t*)(dst->buffer.ptr + dst->buffer.offset), src->buffer.ptr + src->buffer.offset, dst->buffer.size);
    return (int)dst->buffer.size;
}

Error Bytes_marshalJSON(const struct Bytes* self, struct Marshaler *outData) {
    UNUSED(self);
    UNUSED(outData);
    return ErrorCode(ErrorNotImplemented);
}

Error Bytes_unmarshalJSON(struct Bytes* self, struct Marshaler *data) {
    UNUSED(self);
    UNUSED(data);
    return ErrorCode(ErrorNotImplemented);
}

Bytes Bytes_new(buffer_t *b, size_t n) {
    Bytes init = { {0, 0, 0},
                 };
    if ( b ) {
        init.buffer.size = n;
        init.buffer.ptr = b->ptr;
        init.buffer.offset = b->offset;
        b->offset += n;
    }
    return init;
}


Bytes Bytes_init(Byte_t *v, size_t n) {
    buffer_t buffer = { (uint8_t*)v, n, 0};
    return Bytes_new(&buffer, n);
}
