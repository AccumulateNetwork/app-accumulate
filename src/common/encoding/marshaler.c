
#include <common/encoding/encoding.h>

Marshaler NewMarshaler(buffer_t *buffer) {
    Marshaler init = {buffer->ptr + buffer->offset, buffer->size - buffer->offset, 0};
    return init;
}

Unmarshaler NewUnmarshaler(buffer_t *buffer, buffer_t *mempool) {
    Unmarshaler init = {buffer->ptr + buffer->offset, buffer->size - buffer->offset, 0};
    if ( mempool ) {
        //todo: add mempool for allocation
    }
    return init;
}

int marshalerWriteField(Marshaler *m, uint64_t field) {
    return marshalerWriteUInt(m,field);
}

int marshalerWriteInt(Marshaler *m, int64_t n) {
    CHECK_ERROR_INT(m)

    int size = varint_size(n);
    if ( !buffer_can_read(&m->buffer,size) ) {
        return ErrorParameterInsufficientData;
    }

    int r = varint_write((uint8_t*)m->buffer.ptr,m->buffer.offset,n);
    if (r < 0 || r != size) {
        return ErrorVarIntWrite;
    }
    m->buffer.offset += size;

    return size;
}

int marshalerWriteUInt(Marshaler *m, uint64_t n) {
    CHECK_ERROR_INT(m)

    int size = uvarint_size(n);
    if ( !buffer_can_read(&m->buffer,size) ) {
        return ErrorParameterInsufficientData;
    }

    int r = uvarint_write((uint8_t*)m->buffer.ptr,m->buffer.offset,n);
    if (r < 0 || r != size) {
        return ErrorUVarIntWrite;
    }
    m->buffer.offset += size;

    return size;
}

int marshalerWriteVarInt(Marshaler *m, const VarInt *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    int64_t n = 0;
    int size = varint_read(v->data.buffer.ptr + v->data.buffer.offset, v->data.buffer.size - v->data.buffer.offset, &n);
    if ( !size ) {
        return ErrorVarIntRead;
    }

    if ( !buffer_can_read(&m->buffer,size) ) {
        return ErrorParameterInsufficientData;
    }

    int r = varint_write((uint8_t*)m->buffer.ptr,m->buffer.offset,n);
    if (r < 0 || r != size) {
        return ErrorVarIntWrite;
    }
    m->buffer.offset += size;

    return size;
}

int marshalerWriteUVarInt(Marshaler *m,const UVarInt *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    uint64_t n = 0;
    int size = uvarint_read(v->data.buffer.ptr + v->data.buffer.offset, v->data.buffer.size - v->data.buffer.offset, &n);
    if ( !size ) {
        return ErrorUVarIntRead;
    }

    if ( !buffer_can_read(&m->buffer,size) ) {
        return ErrorParameterInsufficientData;
    }

    int r = uvarint_write((uint8_t*)m->buffer.ptr,m->buffer.offset,n);
    if (r < 0 || r != size) {
        return ErrorUVarIntWrite;
    }

    m->buffer.offset += size;

    return size;
}
buffer_t marshalerGetEncodedBuffer(Marshaler *m) {
    buffer_t ret = {m->buffer.ptr, m->buffer.offset,0};
    return ret;
}

int marshalerWriteBytes(Marshaler *m, const struct Bytes *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    int size = Bytes_binarySizeStatic(v);
    if ( !buffer_can_read(&m->buffer,size) ) {
        return ErrorParameterInsufficientData;
    }

    int offset = uvarint_write((uint8_t*)m->buffer.ptr,m->buffer.offset,size);

    //the buffer points to the data buffer, so if this passes, there is enough memory left in data pool
    if (!buffer_seek_cur(&m->buffer, offset)) {
        return ErrorMempoolFull;
    }

    int r = marshalerWriteRaw(m, v);
    if (IsError(ErrorCode(r))) {
        //if we somehow fail, then revert the buffers.
        m->buffer.offset -= offset;
        return r;
    }

    return r + offset;
}

int marshalerWriteBytes32(Marshaler *m, const struct Bytes32 *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    Error e = Bytes32_valid(&v->data);
    if ( IsError(e) ) {
        return e.code;
    }
    return marshalerWriteRaw(m, &v->data);
}

int marshalerWriteBytes64(Marshaler *m, const struct Bytes64 *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    Error e = Bytes64_valid(&v->data);
    if ( IsError(e) ) {
        return e.code;
    }
    return marshalerWriteRaw(m, &v->data);
}

int marshalerWriteRaw(Marshaler *m, const struct  Bytes *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    size_t size = v->buffer.size - v->buffer.offset;
    if ( !buffer_can_read(&m->buffer,size) ) {
        return ErrorParameterInsufficientData;
    }

    //the buffer points to the data buffer, so if this passes, there is enough memory left in data pool to increment data size
    if ( !buffer_copy(&v->buffer,(uint8_t*)m->buffer.ptr + m->buffer.offset, size) ) {
        return ErrorMempoolFull;
    }

    m->buffer.offset += size;

    return (int)size;
}

int marshalerWriteBigInt(Marshaler *m, const struct BigInt *v) {
    CHECK_ERROR_INT(v)
    CHECK_ERROR_INT(m)
    if ( !v->data.buffer.ptr ) {
        return ErrorParameterNil;
    }
    return marshalerWriteBytes(m, &v->data);
}

int marshalerWriteString(Marshaler *m, const struct String *v) {
    CHECK_ERROR_INT(v)
    CHECK_ERROR_INT(m)
    Error e = String_valid(&v->data);
    if ( IsError(e) ) {
        return e.code;
    }
    Bytes s;
    s.buffer.ptr = v->data.buffer.ptr + v->data.buffer.offset;
    s.buffer.offset = 0;
    size_t size = v->data.buffer.size - v->data.buffer.offset;
    size_t len = strlen((const char *) s.buffer.ptr);
    s.buffer.size = size < len ? size : len;

    return marshalerWriteBytes(m, &v->data);
}

int marshalerWriteUrl(Marshaler *m, const struct Url *v) {
    CHECK_ERROR_INT(v)
    String s = { v->data };
    return marshalerWriteString(m, &s);
}

int unmarshalerReadInt(Marshaler *m, int64_t *n) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(n)

    uint8_t a[10] = {0};
    VarInt v = {.data.buffer.ptr = (uint8_t*)a, .data.buffer.offset = 0, .data.buffer.size = sizeof(a)};
    int r = unmarshalerReadVarInt(m, &v);
    if (IsError(ErrorCode(r))) {
        return r;
    }

    return VarInt_get(&v,n).code;
}

int unmarshalerReadUInt(Marshaler *m, uint64_t *field) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(field)

    uint8_t a[10] = {0};
    UVarInt v = {.data.buffer.ptr = (uint8_t*)a, .data.buffer.offset = 0, .data.buffer.size = sizeof(a)};
    int r = unmarshalerReadUVarInt(m, &v);
    if (IsError(ErrorCode(r))) {
        return r;
    }

    return UVarInt_get(&v,field).code;
}

int unmarshalerReadField(Marshaler *m, uint64_t *field) {
    return unmarshalerReadUInt(m,field);
}

int unmarshalerReadVarInt(Marshaler *m, struct VarInt *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    int64_t n = 0;
    int offset = varint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,&n);
    if ( !buffer_can_read(&m->buffer, offset) ) {
        return ErrorVarIntRead;
    }

    //assign the buffer
    v->data.buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->data.buffer.size = offset; //store the number of bytes this takes up.
    m->buffer.offset += offset; //move "cursor"
    return offset;
}

int unmarshalerReadUVarInt(Marshaler *m, struct UVarInt *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    uint64_t size = 0;
    int offset = uvarint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,&size);
    if ( !buffer_can_read(&m->buffer, offset) ) {
        return ErrorVarIntRead;
    }

    v->data.buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->data.buffer.size = offset; //store the number of bytes this takes up.
    m->buffer.offset += offset;
    return offset;
}

int unmarshalerReadBytes(Marshaler *m, struct Bytes *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    uint64_t size = 0;
    int offset = uvarint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,&size);
    if ( !buffer_can_read(&m->buffer, size + offset) ) {
        return ErrorParameterInsufficientData;
    }

    m->buffer.offset += offset;

    v->buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->buffer.offset = 0;
    v->buffer.size = size;

    m->buffer.offset += size;
    return (int)size;
}

int unmarshalerReadBytesRaw(Marshaler *m, struct Bytes *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    if ( !buffer_can_read(&m->buffer, v->buffer.size - v->buffer.offset ) ) {
        return ErrorParameterInsufficientData;
    }

    size_t size = v->buffer.size - v->buffer.offset;
    v->buffer.ptr = m->buffer.ptr + m->buffer.offset;
    m->buffer.offset += size;

    return (int)size;

}
int unmarshalerReadBytes32(Marshaler *m, struct Bytes32 *v) {
    CHECK_ERROR_INT(v)
    if (Bytes32_binarySize(v) != 32) {
        return ErrorInvalidObject;
    }
    return unmarshalerReadBytesRaw(m,&v->data);
}

int unmarshalerReadBytes64(Marshaler *m, struct Bytes64 *v) {
    CHECK_ERROR_INT(v)
    if (Bytes64_binarySize(v) != 64) {
        return ErrorInvalidObject;
    }
    return unmarshalerReadBytesRaw(m,&v->data);
}

int unmarshalerReadBigInt(Marshaler *m, struct BigInt *v) {
    CHECK_ERROR_INT(v)
    return unmarshalerReadBytes(m,&v->data);
}

int unmarshalerReadString(Marshaler *m, struct String *v) {
    return unmarshalerReadBytes(m,&v->data);
}
