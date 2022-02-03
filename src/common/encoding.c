
#include "encoding.h"

Error Error_init(Error *e) {
    Error err = ErrorCode[ErrorNone];
    if ( e ) {
        *e = err;
    }
    return err;
}
int Bytes_binarySizeStatic(const struct Bytes *self) {
    if (!self) {
        return 0;
    }
    return self->buffer.size;
}

int Bytes_binarySizeDynamic(const struct Bytes *self) {
    if (!self) {
        return 0;
    }
    int n = varint_size(self->buffer.size);
    return n + self->buffer.size;
}

Error Bytes_marshalBinaryDynamic(const struct Bytes*self, struct Marshaler *outData) {
    if ( !outData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    int size = self->BinarySize(self);
    if ( !buffer_can_read(&outData->cache,size) ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    int offset = varint_write((uint8_t*)outData->cache.ptr,outData->cache.offset,self->buffer.size);

    memmove((uint8_t*)outData->cache.ptr + outData->cache.offset + offset, self->buffer.ptr + self->buffer.offset, size-offset);
    outData->cache.offset += size;
    outData->data.buffer.size += size;
    return ErrorCode[ErrorNone];
}


Error Bytes_unmarshalBinaryDynamic(Bytes* self, const Marshaler *inData) {

    if ( !inData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    uint64_t size = 0;
    int offset = varint_read(inData->data.buffer.ptr + inData->data.buffer.offset,inData->data.buffer.size,&size);
    if ( !buffer_can_read(&inData->data.buffer, size + offset ) ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    if ( self->buffer.size < size ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    self->buffer.size = size;
    memmove((uint8_t*)self->buffer.ptr + self->buffer.offset, inData->data.buffer.ptr + inData->data.buffer.offset + offset, size);
    return ErrorCode[ErrorNone];
}

Error Bytes_marshalBinaryStatic(const struct Bytes*self, struct Marshaler *outData) {
    if ( !outData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    int size = self->BinarySize(self);
    if ( !buffer_can_read(&outData->cache,size) ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    memmove((uint8_t*)outData->cache.ptr + outData->cache.offset, self->buffer.ptr + self->buffer.offset, size);
    outData->cache.offset += size;
    outData->data.buffer.size += size;
    return ErrorCode[ErrorNone];
}

Error Bytes_unmarshalBinaryStatic(Bytes* self, const Marshaler *inData) {
    if ( !inData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    if ( inData->data.buffer.size < self->buffer.size) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    memmove((uint8_t*)self->buffer.ptr + self->buffer.offset, inData->data.buffer.ptr + inData->data.buffer.offset, self->buffer.size);
    return ErrorCode[ErrorNone];
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

int Bytes_copy(Bytes *b1, const Bytes *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    if ( b1->buffer.size < b2->buffer.size ) {
        return 0;
    }

    memmove((uint8_t*)(b1->buffer.ptr + b1->buffer.offset), b2->buffer.ptr + b2->buffer.offset, b1->buffer.size);
    return b1->buffer.size;
}

Error Bytes_marshalJSON(const struct Bytes* self, struct Marshaler *outData) {
    return ErrorCode[ErrorNotImplemented];
}

Error Bytes_unmarshalJSON(struct Bytes* self, const struct Marshaler *data) {
    return ErrorCode[ErrorNotImplemented];
}

Bytes Bytes_init(Bytes *b, buffer_t *buffer, int size) {
    Bytes init = { {0, 0, 0},
                 Bytes_binarySizeDynamic,
                 Bytes_equal,
                 Bytes_copy,
                 Bytes_marshalBinaryDynamic,
                 Bytes_unmarshalBinaryDynamic,
                 Bytes_marshalJSON,
                 Bytes_unmarshalJSON};
    if ( buffer ) {
        init.buffer.size = size;
        init.buffer.ptr = buffer->ptr;
        init.buffer.offset = buffer->offset;
        buffer->offset += size;
    }
    if ( b ) {
        *b = init;
    }
    return init;
}


Error Bytes32_valid(const Bytes*v) {
    if (!v) {
        return ErrorCode[ErrorParameterNil];
    }
    if (!v->buffer.ptr || v->buffer.size != 32) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    return ErrorCode[ErrorNone];
}

Error Bytes32_get(const struct Bytes *v, Bytes *out) {
    Error e = Bytes32_valid(v);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if (!out) {
        return ErrorCode[ErrorParameterNil];
    }
    if (out->buffer.size < 32) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    int n = v->Copy(out, v);
    if ( n != 32 ) {
        return ErrorCode[ErrorBadCopy];
    }
    return e;
}

Error Bytes32_set(struct Bytes *v, const Bytes *in) {
    Error e = Bytes32_valid(v);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if (!in) {
        return ErrorCode[ErrorParameterNil];
    }
    if (in->buffer.size < 32) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    int n = v->Copy(v, in);
    if ( n != 32 ) {
        return ErrorCode[ErrorBadCopy];
    }
    return e;
}


Error Bytes64_valid(const Bytes*v) {
    if (!v) {
        return ErrorCode[ErrorParameterNil];
    }
    if (!v->buffer.ptr || v->buffer.size != 64) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    return ErrorCode[ErrorNone];
}

Error Bytes64_get(const struct Bytes *v, Bytes *out) {
    Error e = Bytes64_valid(v);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if (!out) {
        return ErrorCode[ErrorParameterNil];
    }
    if (out->buffer.size < 64) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    int n = v->Copy(out, v);
    if ( n != 64 ) {
        return ErrorCode[ErrorBadCopy];
    }
    return e;
}

Error Bytes64_set(struct Bytes *v, const Bytes *in) {
    Error e = Bytes64_valid(v);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if (!in) {
        return ErrorCode[ErrorParameterNil];
    }
    if (in->buffer.size < 64) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    int n = v->Copy(v, in);
    if ( n != 64 ) {
        return ErrorCode[ErrorBadCopy];
    }
    return e;
}


Error VarInt_valid(const Bytes *v) {
    if (!v) {
        return ErrorCode[ErrorParameterNil];
    }
    if (v->buffer.size != sizeof(uint64_t)) {
        return ErrorCode[ErrorBufferTooSmall];
    }
    return ErrorCode[ErrorNone];
}

Error VarInt_set(Bytes *v, uint64_t n) {
    Error e = VarInt_valid(v);
    if ( e.code != ErrorNone ) {
        return e;
    }

    *(uint64_t*)(v->buffer.ptr+v->buffer.offset) = n;
    return ErrorCode[ErrorNone];
}

Error VarInt_get(const Bytes *v, uint64_t *n) {
    Error e = VarInt_valid(v);
    if (e.code != ErrorNone) {
        return e;
    }

    if (!n) {
        return ErrorCode[ErrorParameterNil];
    }

    *n = *(uint64_t*)(v->buffer.ptr+v->buffer.offset);
    return ErrorCode[ErrorNone];
}

int VarInt_binarySize(const Bytes *v) {
    Error e = VarInt_valid(v);
    if ( e.code != ErrorNone ) {
        return 0;
    }

    uint64_t val = *(uint64_t*)(v->buffer.ptr+v->buffer.offset);
    return (int)varint_size(val);
}

Error VarInt_marshalBinary(const Bytes *self, struct Marshaler *outData) {
    if ( !outData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    int size = VarInt_binarySize(self);
    if ( !buffer_can_read(&outData->cache,size) ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    int r = varint_write((uint8_t*)outData->cache.ptr,outData->cache.offset,size);
    if (r < 0) {
        return ErrorCode[ErrorVarIntWrite];
    }
    outData->cache.offset += size;
    outData->data.buffer.size += size;
    return ErrorCode[ErrorNone];
}

Error VarInt_unmarshalBinary(Bytes* self, const Marshaler *inData) {
    Error e = VarInt_valid(self);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !inData ) {
        return ErrorCode[ErrorParameterNil];
    }

    int offset = varint_read((uint8_t*)inData->data.buffer.ptr+inData->data.buffer.offset,
                             inData->data.buffer.size,
                             (uint64_t*)(self->buffer.ptr+self->buffer.offset));
    if ( offset < 0 ) {
        return ErrorCode[ErrorVarIntRead];
    }

    return e;
}


VarInt VarInit_init(VarInt *v, buffer_t *buffer) {
    VarInt init = { { {0,0,0},
                    VarInt_binarySize,
                    Bytes_equal,
                    Bytes_copy,
                    VarInt_marshalBinary,
                    VarInt_unmarshalBinary,
                    Bytes_marshalJSON,
                    Bytes_unmarshalJSON},
                    VarInt_get,
                    VarInt_set,
                  };
    if (buffer) {
        int sizeNeeded = sizeof(uint64_t);
        if ( buffer->size - buffer->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = buffer->ptr;
        init.data.buffer.offset = buffer->offset;
        init.data.buffer.size = sizeNeeded;
        buffer->offset += sizeNeeded;
    }

    if (v) {
        *v = init;
    }
    return init;
}


Error BigInt_valid(const Bytes *s) {
    if (!s ) {
        return ErrorCode[ErrorInvalidBigInt];
    }
    if ( s->buffer.size != 32 && s->buffer.ptr != 0) {
        return ErrorCode[ErrorInvalidBigInt];
    }
    return ErrorCode[ErrorNone];
}

Error BigInt_get(const struct Bytes*s, uint256_t *v) {
    Error e = BigInt_valid(s);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !v ) {
        return ErrorCode[ErrorParameterNil];
    }
    //conv
    readu256BE((uint8_t*)s->buffer.ptr+s->buffer.offset,v);
    return ErrorCode[ErrorNone];
}

Error BigInt_set(struct Bytes*s, const uint256_t *v) {
    Error e = BigInt_valid(s);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !v ) {
        return ErrorCode[ErrorParameterNil];
    }
    //conv

    writeu256BE((uint256_t*)v,(uint8_t*)s->buffer.ptr+s->buffer.offset);
    return ErrorCode[ErrorNone];
}

BigInt BigInit_init(BigInt *v, buffer_t *buffer) {
    BigInt init = { { {0,0,0},
                    Bytes_binarySizeStatic,
                    Bytes_equal,
                    Bytes_copy,
                    Bytes_marshalBinaryStatic,
                    Bytes_unmarshalBinaryStatic,
                    Bytes_marshalJSON,
                    Bytes_unmarshalJSON},
                    BigInt_get,
                    BigInt_set,
                  };
    if (buffer) {
        int sizeNeeded = 32;
        if ( buffer->size - buffer->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = buffer->ptr;
        init.data.buffer.offset = buffer->offset;
        init.data.buffer.size = sizeNeeded;
        buffer->offset += sizeNeeded;
    }

    if (v) {
        *v = init;
    }
    return init;
}


Bytes32 Bytes32_init(Bytes32 *v, buffer_t *buffer) {
    Bytes32 init = { { {0,0,0},
                    Bytes_binarySizeStatic,
                    Bytes_equal,
                    Bytes_copy,
                    Bytes_marshalBinaryStatic,
                    Bytes_unmarshalBinaryStatic,
                    Bytes_marshalJSON,
                    Bytes_unmarshalJSON},
                    Bytes32_get,
                    Bytes32_set,
                  };
    if (buffer) {
        int sizeNeeded = 32;
        if ( buffer->size - buffer->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = buffer->ptr;
        init.data.buffer.offset = buffer->offset;
        init.data.buffer.size = sizeNeeded;
        buffer->offset += sizeNeeded;
    }

    if (v) {
        *v = init;
    }
    return init;
}


Bytes64 Bytes64_init(Bytes64 *v, buffer_t *buffer) {
    Bytes64 init = { { {0,0,0},
                    Bytes_binarySizeStatic,
                    Bytes_equal,
                    Bytes_copy,
                    Bytes_marshalBinaryStatic,
                    Bytes_unmarshalBinaryStatic,
                    Bytes_marshalJSON,
                    Bytes_unmarshalJSON},
                    Bytes64_get,
                    Bytes64_set,
                  };
    if (buffer) {
        int sizeNeeded = 64;
        if ( buffer->size - buffer->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = buffer->ptr;
        init.data.buffer.offset = buffer->offset;
        init.data.buffer.size = sizeNeeded;
        buffer->offset += sizeNeeded;
    }

    if (v) {
        *v = init;
    }
    return init;
}

Error String_valid(const Bytes *s) {
    if (!s ) {
        return ErrorCode[ErrorInvalidString];
    }
    if ( s->buffer.size != 32 && s->buffer.ptr != 0) {
        return ErrorCode[ErrorInvalidString];
    }
    return ErrorCode[ErrorNone];
}

Error String_get(const struct Bytes*s, char *v, int vlen) {
    Error e = String_valid(s);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !v ) {
        return ErrorCode[ErrorParameterNil];
    }
    if (vlen < s->buffer.size ) {
        return ErrorCode[ErrorBufferTooSmall];
    }

    strncpy((char*)v,(const char*)s->buffer.ptr+s->buffer.offset,s->buffer.size);
    return ErrorCode[ErrorNone];
}

Error String_set(struct Bytes*s, const char *v) {
    Error e = String_valid(s);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !v ) {
        return ErrorCode[ErrorParameterNil];
    }

    if (strlen(v) > s->buffer.size) {
        return ErrorCode[ErrorBufferTooSmall];
    }

    memset((void*)(s->buffer.ptr+s->buffer.offset),0,s->buffer.size);
    strncpy((char*)(s->buffer.ptr+s->buffer.offset),v,s->buffer.size);
    return ErrorCode[ErrorNone];
}

String String_init(String *s, buffer_t *buffer, int size) {
    String init;

    Bytes_init(&init.data,buffer, size);

    init.get = String_get;
    init.set = String_set;

    if ( s ) {
        *s = init;
    }
    return init;
}

Marshaler Marshaler_init(Marshaler *v, buffer_t *buffer ) {
    Marshaler init;
    if (buffer) {
        init.data.buffer.size = 0;
        init.cache.size = buffer->size;
        init.data.buffer.ptr = init.cache.ptr = buffer->ptr;
        init.data.buffer.offset = init.cache.offset = buffer->offset;
    }
    if (v) {
        *v = init;
    }
    return init;
}
