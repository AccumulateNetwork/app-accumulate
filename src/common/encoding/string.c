
#include "encoding.h"

ENCODE_COPY(String)
ENCODE_EQUAL(String)

int String_binarySize(const String *v) {
    CHECK_ERROR_INT(v)
    CHECK_ERROR_INT(v->data.buffer.ptr)
    Bytes s;
    s.buffer.ptr = v->data.buffer.ptr + v->data.buffer.offset;
    s.buffer.offset = 0;
    int size = v->data.buffer.size - v->data.buffer.offset;
    int len = strlen((const char *) s.buffer.ptr);
    s.buffer.size = size < len ? size : len;

    return Bytes_binarySizeDynamic(&s);
}


Error String_valid(const Bytes *v) {
    if (!v ) {
        return ErrorCode(ErrorInvalidString);
    }
    if ( !v->buffer.ptr ) {
        return ErrorCode(ErrorInvalidString);
    }

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

    strncpy((char*)s,(const char*)v->data.buffer.ptr+v->data.buffer.offset,slen);
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
    strncpy((char*)(v->data.buffer.ptr+v->data.buffer.offset),s,strlen(s));
    return ErrorCode(ErrorNone);
}

String String_new(buffer_t *b, size_t n) {

    String init = {  {0,0,0}};

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
