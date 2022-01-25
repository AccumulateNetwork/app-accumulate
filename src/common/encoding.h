#ifndef ENCODING_H
#define ENCODING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <common/jsmn.h>
#include <common/uint256.h>
#include <common/varint.h>

typedef struct Error {
   int code;
   char err[64];
} Error;

enum ErrorEnum {
    ErrorOk = 0,
    ErrorParameterNil = 1,
    ErrorParameterInsufficientData = 2,
};

static Error Error_init(Error *e) {
    Error err = { 0, {0} };
    if ( e ) {
        *e = err;
    }
    return err;
}

typedef struct Bytes {
   size_t len;
   uint8_t *data;
   int (*BinarySize)(const struct Bytes *);
   bool (*Equal)(const struct Bytes*, const struct Bytes*);
   int (*Copy)(struct Bytes*, const struct Bytes*);
   Error (*MarshalBinary)(const struct Bytes*, struct Bytes *outData);
   Error (*UnmarshalBinary)(struct Bytes*,const struct Bytes* data);
} Bytes;

Error Bytes_marshalBinary(const struct Bytes*self, struct Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    int size = self->BinarySize(self);
    if ( outData->len < size ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    int offset = varint_write(outData->data,0,self->len);

    memmove(&outData->data[offset], self->data, outData->len);
    outData->len = size;
    return ret;
}


Error Bytes_unmarshalBinary(Bytes* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    uint64_t size = 0;
    int offset = varint_read(inData->data,inData->len,&size);
    if ( inData->len < size + offset ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    if ( self->len < size ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    self->len = size;
    memmove(self->data, &inData->data[offset], self->len);
    return ret;
}

typedef struct Bytes32 {
    uint64_t len;
    uint8_t data[32];
    int (*BinarySize)(const struct Bytes32 *);
    bool (*Equal)(const struct Bytes32*, const struct Bytes32*);
    int (*Copy)(struct Bytes32*, const struct Bytes32*);
    Error (*MarshalBinary)(const struct Bytes32*, Bytes *outData);
    Error (*UnmarshalBinary)(struct Bytes32*,const Bytes* data);
} Bytes32;


typedef struct Bytes64 {
    uint64_t len;
    uint8_t data[64];
    int (*BinarySize)(const struct Bytes64 *);
    bool (*Equal)(const struct Bytes64*, const struct Bytes64*);
    int (*Copy)(struct Bytes64*, const struct Bytes64*);
    Error (*MarshalBinary)(const struct Bytes64*, Bytes *outData);
    Error (*UnmarshalBinary)(struct Bytes64*,const Bytes* data);
} Bytes64;

Error Bytes64_marshalBinary(const Bytes64* self,Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }
    if ( outData->len < 64 ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    outData->len = 64;
    memmove(outData->data, self->data, outData->len);
    return ret;
}

typedef struct String {
   Bytes string;
   int (*BinarySize)(const struct String *);
   bool (*Equal)(const struct String*, const struct String*);
   int (*Copy)(struct String*, const struct String*);
   Error (*MarshalBinary)(const struct String*, Bytes *outData);
   Error (*UnmarshalBinary)(struct String*,const Bytes* data);
} String;


typedef struct BigInt {
    uint256_t bigInt;
    int (*BinarySize)(const struct BigInt *);
    bool (*Equal)(const struct BigInt*, const struct BigInt*);
    int (*Copy)(struct BigInt*, const struct BigInt*);
    Error (*MarshalBinary)(const struct BigInt*, Bytes *outData);
    Error (*UnmarshalBinary)(struct BigInt*,const Bytes* data);
} BigInt;


static String String_init(String *s, uint8_t *buffer, int bufferLen);

int String_binarySize(const String *s) {
    if ( !s ) {
        return 0;
    }
    int size = strlen((const char*)s->string.data);
    size += varint_size(size);
    return size;
}

int Bytes_binarySize(const Bytes *s) {
    if ( !s ) {
        return 0;
    }
    return s->len+varint_size(s->len);
}

int Bytes32_binarySize(const Bytes32 *s) {
    if ( !s ) {
        return 0;
    }
    return s->len;
}

int Bytes64_binarySize(const Bytes64 *s) {
    if ( !s ) {
        return 0;
    }
    return s->len;
}

int BigInt_binarySize(const BigInt *s) {
    if ( !s ) {
        return 0;
    }
    return 32;
}


static bool Bytes_equal(const Bytes *b1,const Bytes *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }
    if ( b1->len != b2->len ) {
        return false;
    }
    return memcmp(b1->data, b2->data, b1->len)==0;
}

static int Bytes_copy(Bytes *b1, const Bytes *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    if ( b1->len < b2->len ) {
        return 0;
    }

    memmove(b1->data, b2->data, b1->len);
    return b1->len;
}

static Bytes Bytes_init(Bytes *b, uint8_t *buffer, uint64_t len) {
    Bytes init = { 0, 0,
                   Bytes_binarySize,
                   Bytes_equal,
                   Bytes_copy,
                   Bytes_marshalBinary,
                   Bytes_unmarshalBinary };
    if ( len && buffer ) {
        init.len = len;
        init.data = buffer;
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
    if ( b1->len != b2->len || b1->len != 32 || b2->len != 32 ) {
        return false;
    }
    return memcmp(b1->data, b2->data, b1->len)==0;
}


static int Bytes32_copy( Bytes32 *b1, const Bytes32 *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    memcpy(b1->data, b2->data, b1->len);
    return b1->len;
}

Error Bytes32_marshalBinary(const Bytes32* self,Bytes *outData) {
    Error ret = Error_init((void*)0);
    if ( !outData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }
    if ( outData->len < 32 ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    outData->len = 32;
    memmove(outData->data, self->data, outData->len);
    return ret;
}

Error Bytes32_unmarshalBinary(Bytes32* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    if ( inData->len < 32 ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    self->len = 32;
    memmove(self->data, inData->data, self->len);
    return ret;
}


static Bytes32 Bytes32_init(Bytes32 *b) {
    Bytes32 init = { 32, {0},
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

    if ( inData->len < 64 ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    self->len = 64;
    memmove(self->data, inData->data, self->len);
    return ret;
}

static bool Bytes64_equal(const Bytes64 *b1, const Bytes64 *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }

    if ( b1->len != b2->len || b1->len != 64 || b2->len != 64 ) {
        return false;
    }

    return memcmp(b1->data, b2->data, b1->len)==0;
}

static int Bytes64_copy(Bytes64 *b1, const Bytes64 *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    memcpy(b1->data, b2->data, b1->len);
    return b1->len;
}

static Bytes64 Bytes64_init(Bytes64 *b) {
    Bytes64 init = { 64, {0},
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
    clone.string.len = strlen((char*)self->string.data);
    clone.string.data = self->string.data;
    return clone.string.MarshalBinary(&clone.string,outData);
}


Error String_unmarshalBinary(String* self, const Bytes *inData) {
    return inData->UnmarshalBinary(&self->string, inData);
}

static int String_copy(String *b1, const String *b2) {
    if ( !b1 || !b2 ) {
        return 0;
    }
    strncpy((char*)b1->string.data, (char*)b2->string.data, b1->string.len);
    return strlen((char*)b1->string.data);
}

static bool String_equal(const String *b1, const String *b2) {
    if ( !b1 || !b2 ) {
        return false;
    }

    return strncmp((const char*)b1->string.data, (const char*)b2->string.data, b1->string.len)==0;
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
    if ( outData->len < 32 ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    outData->len = 32;
    writeu256BE((uint256_t*)&self->bigInt, outData->data);
    return ret;
}

Error BigInt_unmarshalBinary(BigInt* self, const Bytes *inData) {
    Error ret = Error_init(0);
    if ( !inData || !self ) {
        ret.code = ErrorParameterNil;
        return ret;
    }

    if ( inData->len < 32 ) {
        ret.code = ErrorParameterInsufficientData;
        return ret;
    }

    readu256BE(inData->data, &self->bigInt);
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
