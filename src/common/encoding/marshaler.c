
#include <common/encoding/encoding.h>

Marshaler NewMarshaler(buffer_t *buffer) {
    Marshaler init = {buffer->ptr + buffer->offset, buffer->size - buffer->offset, 0};
    return init;
}

Unmarshaler NewUnmarshaler(buffer_t *buffer, buffer_t *mempool) {
    Unmarshaler init = {.buffer = {buffer->ptr + buffer->offset, buffer->size - buffer->offset, 0},
                        .mempool = {mempool->ptr + mempool->offset,mempool->size - mempool->offset,0}};
    return init;
}

int marshalerWriteField(Marshaler *m, uint64_t field) {
    return marshalerWriteUInt(m,field);
}

void *unmarshalerAlloc(Unmarshaler *m, size_t n) {
    if ( !buffer_can_read(&m->mempool, n) ) {
        return 0;
    }
    void *ret = m->mempool.ptr + m->mempool.offset;
    m->mempool.offset += n;
    return ret;
}

Bytes *unmarshalerNewByteBuffer(Unmarshaler *m, size_t n) {
    if ( !buffer_can_read(&m->mempool, sizeof(Bytes)*n) ) {
        return 0;
    }
    Bytes *ret = (Bytes*)(m->mempool.ptr + m->mempool.offset);
    m->mempool.offset += sizeof(Bytes) * n;
    return ret;
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

int marshalerWriteRawJson(Marshaler *m, const struct RawJson *v) {
    CHECK_ERROR_INT(v)
    String s = { v->data };
    return marshalerWriteString(m, &s);
}

int unmarshalerReadInt(Unmarshaler *m, int64_t *n) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(n)

    int offset = varint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,n);
    m->buffer.offset += offset;
    return offset;
}

int unmarshalerReadByte(Unmarshaler *m, uint8_t *field) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(field)

    *field = m->buffer.ptr[m->buffer.offset];;
    m->buffer.offset++;
    return 1;
}

int unmarshalerReadUInt(Unmarshaler *m, uint64_t *field) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(field)

    int offset = uvarint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,field);
    m->buffer.offset += offset;
    return offset;
}

int unmarshalerPeekField(Unmarshaler *m, uint64_t *field) {
    Unmarshaler m2 = *m;
    return unmarshalerReadField(&m2, field);
}

int unmarshalerReadField(Unmarshaler *m, uint64_t *field) {
    uint8_t byte = 0;
    int b = unmarshalerReadByte(m, &byte);//unmarshalerReadField(&m2, field);
    *field = (uint64_t)byte;
    return b;
}

int unmarshalerReadVarInt(Unmarshaler *m, struct VarInt *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    int64_t n = 0;
    int offset = varint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,&n);

    //assign the buffer
    v->data.buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->data.buffer.size = offset; //store the number of bytes this takes up.
    m->buffer.offset += offset; //move "cursor"
    return offset;
}

int unmarshalerReadUVarInt(Unmarshaler *m, struct UVarInt *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    uint64_t size = 0;
    int offset = uvarint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,&size);

    v->data.buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->data.buffer.size = offset; //store the number of bytes this takes up.
    m->buffer.offset += offset;
    return offset;
}

int unmarshalerReadBytes(Unmarshaler *m, struct Bytes *v) {
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
    return (int)size+offset;
}

int unmarshalerReadBytesRaw(Unmarshaler *m, struct Bytes *v, size_t size) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    if ( !buffer_can_read(&m->buffer, v->buffer.size - v->buffer.offset ) ) {
        return ErrorParameterInsufficientData;
    }

    v->buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->buffer.offset = 0;
    v->buffer.size = size;
    m->buffer.offset += size;

    return (int)size;

}
int unmarshalerReadBytes32(Unmarshaler *m, struct Bytes32 *v) {
    CHECK_ERROR_INT(v)
    return unmarshalerReadBytesRaw(m,&v->data, 32);
}

int unmarshalerReadBytes64(Unmarshaler *m, struct Bytes64 *v) {
    CHECK_ERROR_INT(v)
    return unmarshalerReadBytesRaw(m,&v->data, 64);
}

int unmarshalerReadBigInt(Unmarshaler *m, struct BigInt *v) {
    CHECK_ERROR_INT(v)
    return unmarshalerReadBytes(m,&v->data);
}

int unmarshalerReadString(Unmarshaler *m, struct String *v) {
    return unmarshalerReadBytes(m,&v->data);
}

int unmarshalerReadRawJson(Unmarshaler *m, struct RawJson *v) {
    return unmarshalerReadBytes(m,&v->data);
}

int unmarshalerReadUrl(Unmarshaler *m, struct Url *v) {
    return unmarshalerReadBytes(m,&v->data);
}
