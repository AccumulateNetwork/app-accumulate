
#include "encoding.h"

static Error Error_init(Error *e) {
    Error err = ErrorCode[ErrorNone];
    if ( e ) {
        *e = err;
    }
    return err;
}

Error Bytes_marshalBinaryDynamic(const struct Bytes*self, struct Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    int size = self->BinarySize(self);
    if ( !buffer_can_read(&outData->buffer,size) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    int offset = varint_write((uint8_t*)outData->buffer.ptr,outData->buffer.offset,self->buffer.size-self->buffer.offset);

    memmove((uint8_t*)outData->buffer.ptr + outData->buffer.offset + offset, self->buffer.ptr + self->buffer.offset, size-offset);
    outData->buffer.offset += size;
    return ret;
}


Error Bytes_unmarshalBinaryDynamic(Bytes* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    uint64_t size = 0;
    int offset = varint_read(inData->buffer.ptr + inData->buffer.offset,inData->buffer.size,&size);
    if ( !buffer_can_read(&inData->buffer, size + offset ) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    if ( self->buffer.size < size ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    self->buffer.size = size;
    memmove((uint8_t*)self->buffer.ptr + self->buffer.offset, inData->buffer.ptr + inData->buffer.offset + offset, size);
    return ret;
}

Error Bytes_marshalBinaryStatic(const struct Bytes*self, struct Bytes *outData) {
    Error ret = ErrorCode[ErrorNone];
    if ( !outData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    int size = self->BinarySize(self);
    if ( !buffer_can_read(&outData->buffer,size) ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    memmove((uint8_t*)outData->buffer.ptr + outData->buffer.offset, self->buffer.ptr + self->buffer.offset, size);
    outData->buffer.offset += size;
    return ret;
}

Error Bytes_unmarshalBinaryStatic(Bytes* self, const Bytes *inData) {
    if ( !inData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    uint64_t size = 0;

    if ( self->buffer.size < size ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    self->buffer.size = size;
    memmove((uint8_t*)self->buffer.ptr + self->buffer.offset, inData->buffer.ptr + inData->buffer.offset, size);
    return ErrorCode[ErrorNone];
}


static bool Bytes_equal(const Bytes *b1,const Bytes *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }
    if ( b1->buffer.size-b1->buffer.offset != b2->buffer.size-b2->buffer.offset ) {
        return false;
    }
    return memcmp(b1->buffer.ptr+b1->buffer.offset, b2->buffer.ptr+b1->buffer.offset, b1->buffer.size-b1->buffer.offset)==0;
}

static int Bytes_copy(Bytes *b1, const Bytes *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    if ( b1->buffer.size-b1->buffer.offset < b2->buffer.size-b2->buffer.offset ) {
        return 0;
    }

    memmove((uint8_t*)b1->buffer.ptr + b1->buffer.offset, b2->buffer.ptr + b2->buffer.offset, b1->buffer.size-b1->buffer.offset);
    return b1->buffer.size - b1->buffer.offset;
}


static Bytes Bytes_init(Bytes *b, uint8_t *buffer, uint64_t len) {
    Bytes init = { {0, 0, 0},
                   Bytes_binarySize,
                   Bytes_equal,
                   Bytes_copy,
                   Bytes_marshalBinary,
                   Bytes_unmarshalBinary };
    if ( len && buffer ) {
        init.buffer.size = len;
        init.buffer.ptr = buffer;
    }
    if ( b ) {
        *b = init;
    }
    return init;
}



static Error VarInt_valid(const VarInt *v) {
    if (!v) {
        return ErrorCode[ErrorParameterNil];
    }
    return ErrorCode[ErrorNone];
}

static Error VarInt_set(const VarInt *v, uint64_t n) {
    if (!v) {
        return ErrorCode[ErrorParameterNil];
    }
    int size = varint_size(n);
    if ( size != v->buffer.size ) {
        return ErrorCode[ErrorResizeRequred];
    }
}

static int VarInt_binarySize(const VarInt *v) {
    if (!v) {
        return 0;
    }
    return varint_size(v->varint);
}

Error VarInt_marshalBinary(const VarInt *self, struct Bytes *outData) {
    if ( !outData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    int size = self->BinarySize(self);
    if ( !buffer_can_read(&outData->buffer,size) ) {
        return ErrorCode[ErrorParameterInsufficientData];
    }

    int r = varint_write((uint8_t*)outData->buffer.ptr,outData->buffer.offset,size);
    if (r < 0) {
        return ErrorCode[ErrorVarIntWrite];
    }
    outData->buffer.offset += size;
    return ErrorCode[ErrorNone];
}

static Error VarInt_unmarshalBinary(VarInt* self, const Bytes *inData) {
    if ( !inData || !self ) {
        return ErrorCode[ErrorParameterNil];
    }

    int offset = varint_read(inData->buffer.ptr+inData->buffer.offset,inData->buffer.size,&self->varint);
    if ( offset < 0 ) {
        return ErrorCode[ErrorVarIntRead];
    }

    return ErrorCode[ErrorNone];
}

static Error VarInt_marshalJSON(const VarInt* v, Bytes *outData) {
    return ErrorCode[ErrorNotImplemented];
}

static Error VarInt_unmarshalJSON(VarInt* v,const struct Bytes *data) {
    return ErrorCode[ErrorNotImplemented];
}

static VarInt VarInit_init(VarInt *v, buffer_t *buffer) {
    VarInt init = { { {0,0,0},
                    VarInt_binarySize,
                    Bytes_equal,
                    Bytes_copy,
                    Bytes_marshalBinaryStatic,
                    Bytes_unmarshalBinaryStatic,
                    Bytes_marshalJSON,
                    Bytes_unmarshalJSON},
                    ;
    if (v) {
        *v = init;
    }
    return init;
}


Error BigInt_valid(const BigInt *s) {
    if (!s ) {
        return ErrorCode[ErrorInvalidBigInt];
    }
    if ( s->buffer.size != 32 && s->buffer.ptr != 0) {
        return ErrorCode[ErrorInvalidBigInt];
    }
}

Error BigInt_get(const struct BigInt*s, uint256_t *v) {
    Error e = BigInt_valid(s);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !v ) {
        return ErrorCode[ErrorParameterNil];
    }
    //conv
    readu256BE(s->buffer.ptr+s->buffer.offset,v);
    return ErrorCode[ErrorNone];
}

Error BigInt_set(const struct BigInt*s, const uint256_t *v) {
    Error e = BigInt_valid(s);
    if ( e.code != ErrorNone ) {
        return e;
    }
    if ( !v ) {
        return ErrorCode[ErrorParameterNil];
    }
    //conv
    writeu256BE(v,(uint8_t*)s->buffer.ptr+s->buffer.offset);
    return ErrorCode[ErrorNone];
}




static Bytes32 Bytes32_init(Bytes32 *b) {
    Bytes32 init = { {0},
                   Bytes32_binarySize,
                   Bytes32_equal,
                   Bytes32_copy,
                   Bytes32_marshalBinary,
                   Bytes32_unmarshalBinary};
    if ( b ) {
        *b = init;
    }
    return init;
}

static String String_init(String *s, uint8_t *buffer, int bufferLen) {
    String init;

    Bytes_init(&init.string,buffer,bufferLen);
    init.BinarySize = String_binarySize;
    init.Equal = String_equal;
    init.Copy = String_copy;
    init.MarshalBinary = String_marshalBinary;
    init.UnmarshalBinary = String_unmarshalBinary;


    if ( s ) {
        *s = init;
    }
    return init;
}


static BigInt BigInt_init(BigInt *b) {
    BigInt init;
    zero256(&init.bigInt);
    init.BinarySize = BigInt_binarySize;
    init.Equal = BigInt_equal;
    init.Copy = BigInt_copy;
    init.MarshalBinary = BigInt_marshalBinary;
    init.UnmarshalBinary = BigInt_unmarshalBinary;
    if ( b ) {
        *b = init;
    }
    return init;
}

