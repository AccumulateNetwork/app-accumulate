
#include <common/error.h>
#include <common/varint.h>
#include <common/encoding/encoding.h>

ENCODE_COPY(VarInt)
ENCODE_EQUAL(VarInt)

Error VarInt_valid(const Bytes *v) {
    if (!v) {
        return ErrorCode(ErrorParameterNil);
    }
    if (!v->buffer.ptr) {
        return ErrorCode(ErrorParameterNil);
    }
    if (v->buffer.size != sizeof(uint64_t)) {
        return ErrorCode(ErrorBufferTooSmall);
    }
//    if ( !v->Copy || !v->Equal || !v->BinarySize || !v->MarshalBinary || !v->UnmarshalBinary ) {
//        return ErrorCode(ErrorInvalidObject);
//    }
    return ErrorCode(ErrorNone);
}

Error VarInt_set(VarInt *v, int64_t n) {
    CHECK_ERROR(v)

    int size = varint_size(n);
    if ( size > v->data.buffer.size - v->data.buffer.offset ) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    if ( !varint_write((uint8_t*)v->data.buffer.ptr + v->data.buffer.offset, v->data.buffer.size - v->data.buffer.offset, n) ) {
        return ErrorCode(ErrorVarIntWrite);
    }

    return ErrorCode(ErrorNone);
}

Error VarInt_get(const VarInt *v, int64_t *n) {
    CHECK_ERROR(v)
    Error e = VarInt_valid(&v->data);
    if (e.code != ErrorNone) {
        return e;
    }

    if (!n) {
        return ErrorCode(ErrorParameterNil);
    }

    if ( !varint_read((uint8_t*)v->data.buffer.ptr, v->data.buffer.offset, n) ) {
        return ErrorCode(ErrorVarIntRead);
    }
    return ErrorCode(ErrorNone);
}

int VarInt_binarySize(const VarInt *v) {
    CHECK_ERROR_INT(v)

    int64_t val = 0;
    if ( !varint_read((uint8_t*)v->data.buffer.ptr+v->data.buffer.offset, v->data.buffer.size - v->data.buffer.offset, &val) ) {
        return ErrorUVarIntRead;
    }

    int size = (int)varint_size(val);
    if ( size < 0 || size > MaxVarintLen64 ) {
        return ErrorInvalidObject;
    }
    return size;
}


VarInt VarInt_new(buffer_t *buffer) {
    VarInt init = {{0,0,0}};
    if (buffer) {
        //allocate the maximum size needed
        int sizeNeeded = varint_size(-INT64_MAX);
        if ( buffer->size - buffer->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = buffer->ptr + buffer->offset;
        init.data.buffer.offset = 0;
        init.data.buffer.size = sizeNeeded;
        buffer->offset += sizeNeeded;
    }

    return init;
}
//
//VarInt VarInt_init(VarInt_t *v) {
//    buffer_t buffer = { v, sizeof(size_t), 0};
//    return VarInt_new(&buffer, sizeof (size_t));
//}