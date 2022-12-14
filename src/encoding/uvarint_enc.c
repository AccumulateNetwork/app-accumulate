
#include <common/error.h>
#include <common/varint.h>
#include <encoding/encoding.h>
#include <encoding/uvarint.h>

ENCODE_COPY(UVarInt)
ENCODE_EQUAL(UVarInt)

Error UVarInt_valid(const Bytes *v) {
    if (!v) {
        return ErrorCode(ErrorParameterNil);
    }
    if (v->buffer.size < varint_size(UINT64_MAX)) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    return ErrorCode(ErrorNone);
}

Error UVarInt_set(UVarInt *v, uint64_t n) {
    CHECK_ERROR(v)
    Error e = UVarInt_valid(&v->data);
    if (e.code != ErrorNone) {
        return e;
    }

    size_t size = uvarint_size(n);
    if (size > v->data.buffer.size - v->data.buffer.offset) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    *((uint64_t *) (v->data.buffer.ptr + v->data.buffer.offset)) = n;
    varint_write((uint8_t *) v->data.buffer.ptr, v->data.buffer.offset, n);
    return ErrorCode(ErrorNone);
}

Error UVarInt_get(const UVarInt *v, uint64_t *n) {
    CHECK_ERROR(v)

    if (!v->data.buffer.ptr) {
        return ErrorCode(ErrorParameterNil);
    }

    if (uvarint_read(v->data.buffer.ptr + v->data.buffer.offset,
                     v->data.buffer.size - v->data.buffer.offset,
                     n) < 0) {
        return ErrorCode(ErrorUVarIntRead);
    }
    return ErrorCode(ErrorNone);
}

int UVarInt_binarySize(const UVarInt *v) {
    CHECK_ERROR_INT(v)

    uint64_t val = 0;

    if (uvarint_read((uint8_t *) v->data.buffer.ptr + v->data.buffer.offset,
                     v->data.buffer.size - v->data.buffer.offset,
                     &val) < 0) {
        return ErrorUVarIntRead;
    }

    int size = (int) uvarint_size(val);
    if (size < 0 || size > MaxVarintLen64) {
        return ErrorInvalidObject;
    }
    return size;
}

UVarInt UVarInt_new(buffer_t *buffer) {
    UVarInt init = {{{0, 0, 0}}};
    if (buffer) {
        int sizeNeeded = uvarint_size(UINT64_MAX);
        if ((int) buffer->size - (int) buffer->offset < sizeNeeded) {
            return init;
        }
        init.data.buffer.ptr = buffer->ptr;
        init.data.buffer.offset = buffer->offset;
        init.data.buffer.size = sizeNeeded;
        buffer->offset += sizeNeeded;
    }

    return init;
}
