
#include "encoding.h"

ENCODE_BINARY_SIZE_DYNAMIC(String)
ENCODE_COPY(String)
ENCODE_EQUAL(String)
//ENCODE_MARSHAL_BINARY_DYNAMIC(String)
//ENCODE_UNMARSHAL_BINARY_DYNAMIC(String)

Error String_valid(const Bytes *v) {
    if (!v ) {
        return ErrorCode(ErrorInvalidString);
    }
    if ( v->buffer.size != 32 && v->buffer.ptr != 0) {
        return ErrorCode(ErrorInvalidString);
    }
//    if ( !v->Copy || !v->Equal || !v->BinarySize || !v->MarshalBinary || !v->UnmarshalBinary ) {
//        return ErrorCode(ErrorInvalidObject);
//    }
    return ErrorCode(ErrorNone);
}

Error String_get(const String*v, char *s, size_t slen) {
    CHECK_ERROR(v)
    CHECK_ERROR(s)
    Error e = String_valid(&v->data);
    if ( e.code != ErrorNone ) {
        return e;
    }

    if (slen < v->data.buffer.size ) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    strncpy((char*)s,(const char*)v->data.buffer.ptr+v->data.buffer.offset,v->data.buffer.size);
    return ErrorCode(ErrorNone);
}

Error String_set(String *v, const char *s) {
    CHECK_ERROR(v)
    CHECK_ERROR(s)
    Error e = String_valid(&v->data);
    if ( e.code != ErrorNone ) {
        return e;
    }

    if (strlen(s) > v->data.buffer.size) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    memset((void*)(v->data.buffer.ptr+v->data.buffer.offset),0,v->data.buffer.size);
    //strncpy((char*)(s->data.buffer.ptr+s->data.buffer.offset),(const char*)v->ptr + v->offset,s->data.buffer.size);
    strncpy((char*)(v->data.buffer.ptr+v->data.buffer.offset),v,v->data.buffer.size);
    return ErrorCode(ErrorNone);
}

String String_new(buffer_t *b, size_t n) {

    String init = { { {0,0,0},
                       Bytes_binarySizeStatic,
                       Bytes_equal,
                       Bytes_copy,
                       Bytes_marshalBinaryStatic,
                       Bytes_unmarshalBinaryStatic,
                       Bytes_marshalJSON,
                       Bytes_unmarshalJSON},
    };

    if (b) {
        int sizeNeeded = n;
        if ( b->size - b->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = b->ptr;
        init.data.buffer.offset = b->offset;
        init.data.buffer.size = sizeNeeded;
        b->offset += sizeNeeded;
    }
    return init;
}

String String_init(String_t *v) {
    return String_new(&v, v->size);
}
