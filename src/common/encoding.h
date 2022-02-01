#ifndef ENCODING_H
#define ENCODING_H

//The structures in this file use buffered encoding that requires an external buffer be provided
//This is used in support of the Accumulate types generator.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <common/jsmn.h>
#include <common/uint256.h>
#include <common/varint.h>
#include <common/buffer.h>

typedef struct Error {
   int code;
   char err[64];
} Error;

enum ErrorEnum {
    ErrorNone = 0,
    ErrorUnknown,
    ErrorNotImplemented,
    ErrorTypeNotFound,
    ErrorParameterNil,
    ErrorParameterInsufficientData,
    ErrorBufferTooSmall,
    ErrorVarIntRead,
    ErrorVarIntWrite,
    ErrorResizeRequred,
    ErrorInvalidBigInt,
};

static Error ErrorCode[] = {
    {ErrorNone, {0}},
    {ErrorUnknown, "unknown"},
    {ErrorNotImplemented, "not implemented"},
    {ErrorTypeNotFound, "type not found"},
    {ErrorParameterNil, "parameter is nil"},
    {ErrorParameterInsufficientData,"insufficient buffer size"},
    {ErrorBufferTooSmall,"buffer size too small"},
    {ErrorVarIntRead, "varint read failed"},
    {ErrorVarIntWrite,"varint write failed"},
    {ErrorResizeRequred,"resize required"},
    {ErrorInvalidBigInt,"invalid big int"},
};



static Error Error_init(Error *e) {
    Error err = ErrorCode[ErrorNone];
    if ( e ) {
        *e = err;
    }
    return err;
}

typedef struct Bytes {
   buffer_t buffer;

   int (*BinarySize)(const struct Bytes *);
   bool (*Equal)(const struct Bytes*, const struct Bytes*);
   int (*Copy)(struct Bytes*, const struct Bytes*);
   Error (*MarshalBinary)(const struct Bytes*, struct Bytes *outData);
   Error (*UnmarshalBinary)(struct Bytes*,const struct Bytes* data);
   Error (*MarshalJSON)(const struct Bytes*, struct Bytes *outData);
   Error (*UnmarshalJSON)(struct Bytes*,const struct Bytes *data);
} Bytes;

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

    memmove((uint8_t*)outData->buffer.ptr + outData->buffer.offset + offset, self->buffer.ptr + self->buffer.offset, size);
    outData->buffer.offset += size;
    return ret;
}

Error Bytes_unmarshalBinaryStatic(Bytes* self, const Bytes *inData) {
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

    if ( self->buffer.size-self->buffer.offset < size ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    self->buffer.size = size;
    self->buffer.offset = 0;
    memmove((uint8_t*)self->buffer.ptr + self->buffer.offset, inData->buffer.ptr + inData->buffer.offset + offset, size);
    return ret;
}


typedef struct VarInt {
   Bytes bytes;
   Error (*get)(const struct VarInt *, uint64_t *out);
   Error (*set)(const struct VarInt *, uint64_t *out);
} VarInt;

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

typedef struct Bytes32 {
    buffer_t buffer;
    int (*BinarySize)(const struct Bytes32 *);
    bool (*Equal)(const struct Bytes32*, const struct Bytes32*);
    int (*Copy)(struct Bytes32*, const struct Bytes32*);
    Error (*MarshalBinary)(const struct Bytes32*, Bytes *outData);
    Error (*UnmarshalBinary)(struct Bytes32*,const Bytes* data);
    Error (*MarshalJSON)(const struct Bytes32*, struct Bytes *outData);
    Error (*UnmarshalJSON)(struct Bytes32*,const struct Bytes *data);
} Bytes32;


typedef struct Bytes64 {
    buffer_t buffer;
    int (*BinarySize)(const struct Bytes64 *);
    bool (*Equal)(const struct Bytes64*, const struct Bytes64*);
    int (*Copy)(struct Bytes64*, const struct Bytes64*);
    Error (*MarshalBinary)(const struct Bytes64*, Bytes *outData);
    Error (*UnmarshalBinary)(struct Bytes64*,const Bytes* data);
    Error (*MarshalJSON)(const struct Bytes64*, struct Bytes *outData);
    Error (*UnmarshalJSON)(struct Bytes64*,const struct Bytes *data);
} Bytes64;

Error Bytes64_marshalBinary(const Bytes64* self,Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }
    if ( !buffer_can_read(&outData->buffer, 64) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    outData->buffer.offset += 64;
    memmove((uint8_t*)outData->buffer.ptr + outData->buffer.offset, self->data, 64);
    return ret;
}

typedef struct String {
   Bytes string;
   int (*BinarySize)(const struct String *);
   bool (*Equal)(const struct String*, const struct String*);
   int (*Copy)(struct String*, const struct String*);
   Error (*MarshalBinary)(const struct String*, Bytes *outData);
   Error (*UnmarshalBinary)(struct String*,const Bytes* data);
   Error (*MarshalJSON)(const struct String*, struct Bytes *outData);
   Error (*UnmarshalJSON)(struct String*,const struct Bytes *data);
} String;


typedef struct BigInt {
    uint256_t bigInt;
    buffer_t buffer;
    Error (*get)(const struct BigInt*, uint256_t *);
    Error (*set)(struct BigInt*, const uint256_t *);

    int (*BinarySize)(const struct BigInt *);
    bool (*Equal)(const struct BigInt*, const struct BigInt*);
    int (*Copy)(struct BigInt*, const struct BigInt*);
    Error (*MarshalBinary)(const struct BigInt*, Bytes *outData);
    Error (*UnmarshalBinary)(struct BigInt*,const Bytes* data);
    Error (*MarshalJSON)(const struct BigInt*, struct Bytes *outData);
    Error (*UnmarshalJSON)(struct BigInt*,const struct Bytes *data);
} BigInt;

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

static String String_init(String *s, uint8_t *buffer, int bufferLen);

int String_binarySize(const String *s) {
    if ( !s ) {
        return 0;
    }
    int size = strlen((const char*)(s->string.buffer.ptr +  s->string.buffer.offset));
    size += varint_size(size);
    return size;
}

int Bytes_binarySize(const Bytes *s) {
    if ( !s ) {
        return 0;
    }
    uint32_t l = s->buffer.size - s->buffer.offset;
    return l+varint_size(l);
}

int Bytes32_binarySize(const Bytes32 *s) {
    if ( !s ) {
        return 0;
    }
    return 32;
}

int Bytes64_binarySize(const Bytes64 *s) {
    if ( !s ) {
        return 0;
    }
    return 64;
}

int BigInt_binarySize(const BigInt *s) {
    Error e = BigInt_valid(s);
    if ( e.code != ErrorNone ) {
        return 0;
    }
    return s->buffer.size;
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


static bool Bytes32_equal(const Bytes32 *b1, const Bytes32 *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }
    return memcmp(b1->data, b2->data, 32)==0;
}


static int Bytes32_copy( Bytes32 *b1, const Bytes32 *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    memcpy(b1->data, b2->data, 32);
    return 32;
}

Error Bytes32_marshalBinary(const Bytes32* self,Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }
    if ( !buffer_can_read(&outData->buffer, 32) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    outData->buffer.offset += 32;
    memmove((uint8_t*)outData->buffer.ptr + outData->buffer.size, self->data, 32);
    return ret;
}

Error Bytes32_unmarshalBinary(Bytes32* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    if ( !buffer_can_read(&inData->buffer, 32) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    memmove(self->data, inData->buffer.ptr+inData->buffer.offset, 32);
    return ret;
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

Error Bytes64_unmarshalBinary(Bytes64* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    if ( !buffer_can_read(&inData->buffer, 64) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    memmove(self->data, inData->buffer.ptr + inData->buffer.offset, 64);
    return ret;
}

static bool Bytes64_equal(const Bytes64 *b1, const Bytes64 *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }
    return memcmp(b1->data, b2->data, 64)==0;
}

static int Bytes64_copy(Bytes64 *b1, const Bytes64 *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    memcpy(b1->data, b2->data, 64);
    return 64;
}

static Bytes64 Bytes64_init(Bytes64 *b) {
    Bytes64 init = { {0},
                     Bytes64_binarySize,
                     Bytes64_equal,
                     Bytes64_copy,
                     Bytes64_marshalBinary,
                     Bytes64_unmarshalBinary};
    if ( b ) {
        *b = init;
    }
    return init;
}

Error String_marshalBinary(const String* self, Bytes *outData) {
    //Ensure the self length is the strlen w/o modifying self.
    String clone;
    String_init(&clone,0,0);
    clone.string.buffer.size = strlen((char*)self->string.buffer.ptr);
    clone.string.buffer.ptr = self->string.buffer.ptr;
    return clone.string.MarshalBinary(&clone.string,outData);
}


Error String_unmarshalBinary(String* self, const Bytes *inData) {
    return inData->UnmarshalBinary(&self->string, inData);
}

static int String_copy(String *b1, const String *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    strncpy((char*)b1->string.buffer.ptr, (char*)b2->string.buffer.ptr, b1->string.buffer.size);
    return strlen((char*)b1->string.buffer.ptr);
}

static bool String_equal(const String *b1, const String *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }

    return strncmp((const char*)b1->string.buffer.ptr + b1->string.buffer.offset, (const char*)b2->string.buffer.ptr+b2->string.buffer.offset,
                   b1->string.buffer.size-b1->string.buffer.offset)==0;
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

static bool BigInt_equal(const BigInt *b1, const BigInt *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }
    return equal256((uint256_t*)&b1->bigInt,(uint256_t*)&b2->bigInt);
}


static int BigInt_copy( BigInt *b1, const BigInt *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    copy256(&b1->bigInt, (uint256_t*) &b2->bigInt);
    return 32;
}

Error BigInt_marshalBinary(const BigInt* self,Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }
    if ( !buffer_can_read(&outData->buffer,32) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    writeu256BE((uint256_t*)&self->bigInt, (uint8_t*)outData->buffer.ptr+outData->buffer.offset);
    return ret;
}

Error BigInt_unmarshalBinary(BigInt* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    if ( !buffer_can_read(&inData->buffer,32) ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    readu256BE((uint8_t*)inData->buffer.ptr, &self->bigInt);
    return ret;
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

#endif
