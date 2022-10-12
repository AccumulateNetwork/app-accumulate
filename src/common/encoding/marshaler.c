
#include <common/encoding/encoding.h>

Marshaler NewMarshaler(buffer_t *buffer) {
    Marshaler init = {buffer->ptr + buffer->offset, buffer->size - buffer->offset, 0};
    return init;
}

Unmarshaler NewUnmarshaler(buffer_t *buffer, buffer_t *mempool) {
    Unmarshaler init = {.buffer = {buffer->ptr + buffer->offset, buffer->size - buffer->offset, 0},
                        .mempool = mempool};
    return init;
}

int marshalerWriteField(Marshaler *m, uint64_t field) {
    return marshalerWriteUInt(m,field);
}

void *unmarshalerAlloc(Unmarshaler *m, size_t n) {
    if ( m->mempool == NULL ) {
        return NULL;
    }
    if ( !buffer_can_read(m->mempool, n) ) {
        return NULL;
    }
    void *ret = m->mempool->ptr + m->mempool->offset;
    m->mempool->offset += n;
    return ret;
}

Bytes *unmarshalerNewByteBuffer(Unmarshaler *m, size_t n) {
    if ( m->mempool == NULL ) {
        return NULL;
    }
    if ( !buffer_can_read(m->mempool, sizeof(Bytes)*n) ) {
        return NULL;
    }
    Bytes *ret = (Bytes*)(m->mempool->ptr + m->mempool->offset);
    m->mempool->offset += sizeof(Bytes) * n;
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
    return marshalerWriteBytes(m, &v->data);
}

int marshalerWriteRawJson(Marshaler *m, const struct RawJson *v) {
    return marshalerWriteBytes(m, &v->data);
}

int unmarshalerReadInt(Unmarshaler *m, int64_t *n) {
    int offset = varint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,n);
    m->buffer.offset += offset;
    return offset;
}

int unmarshalerReadByte(Unmarshaler *m, uint8_t *field) {
    if (!buffer_can_read(&m->buffer, 1)) {
        return ErrorBufferTooSmall;
    }
    *field = m->buffer.ptr[m->buffer.offset];
    buffer_seek_cur(&m->buffer, 1);
    return 1;
}

int unmarshalerReadUInt(Unmarshaler *m, uint64_t *field) {
    int ret = buffer_read_uvarint(&m->buffer, field);
    if ( ret < 0 ) {
        return ErrorUVarIntRead;
    }
    return ret;
}

int unmarshalerPeekField(Unmarshaler *m, uint64_t *field) {
    Unmarshaler m2 = *m;
    return unmarshalerReadField(&m2, field);
}

int unmarshalerReadField(Unmarshaler *m, uint64_t *field) {
    uint8_t byte = 0;
    int b = unmarshalerReadByte(m, &byte);
    *field = (uint64_t)byte;
    return b;
}

int unmarshalerReadVarInt(Unmarshaler *m, struct VarInt *v) {
    int64_t n = 0;
    int offset = varint_read(m->buffer.ptr + m->buffer.offset,m->buffer.size - m->buffer.offset,&n);

    //assign the buffer
    v->data.buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->data.buffer.size = offset; //store the number of bytes this takes up.
    v->data.buffer.offset = 0;
    m->buffer.offset += offset; //move "cursor"
    return offset;
}

int unmarshalerReadUVarInt(Unmarshaler *m, struct UVarInt *v) {
    uint64_t n = 0;

    v->data.buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->data.buffer.offset = 0;
    int offset = buffer_read_uvarint(&m->buffer,&n);
    if ( offset < 0 ) {
        return ErrorUVarIntRead;
    }

    v->data.buffer.size = offset;

    return offset;
}

int unmarshalerReadBytes(Unmarshaler *m, struct Bytes *v) {
    uint64_t size = 0;
    int a = unmarshalerReadUInt(m, &size);
    if (IsError(ErrorCode(a))) {
        return a;
    }

    int b = unmarshalerReadBytesRaw(m, v, size);
    if (IsError(ErrorCode(b))) {
        return b;
    }
    return a+b;
}

int unmarshalerReadBytesRaw(Unmarshaler *m, struct Bytes *v, size_t size) {
    if ( !buffer_can_read(&m->buffer, size ) ) {
        return ErrorParameterInsufficientData;
    }

    v->buffer.ptr = m->buffer.ptr + m->buffer.offset;
    v->buffer.offset = 0;
    v->buffer.size = size;

    buffer_seek_cur(&m->buffer, size);
    return (int)size;

}
int unmarshalerReadBytes32(Unmarshaler *m, struct Bytes32 *v) {
    return unmarshalerReadBytesRaw(m,&v->data, 32);
}

int unmarshalerReadBytes64(Unmarshaler *m, struct Bytes64 *v) {
    return unmarshalerReadBytesRaw(m,&v->data, 64);
}

int unmarshalerReadBigInt(Unmarshaler *m, struct BigInt *v) {
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
