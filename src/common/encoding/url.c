
#include "encoding.h"

ENCODE_BINARY_SIZE_DYNAMIC(Url)
ENCODE_COPY(Url)
ENCODE_EQUAL(Url)
//ENCODE_MARSHAL_BINARY_DYNAMIC(Url)
//ENCODE_UNMARSHAL_BINARY_DYNAMIC(Url)

Error Url_valid(const Bytes *v) {
    CHECK_ERROR(v)
    if ( v->buffer.ptr != 0) {
        return ErrorCode(ErrorInvalidString);
    }

    return ErrorCode(ErrorNone);
}

Error Url_get(const Url*v, char *s, size_t slen) {
    CHECK_ERROR(v)
    CHECK_ERROR(s)
    Error e = Url_valid(&v->data);
    if ( e.code != ErrorNone ) {
        return e;
    }

    if (slen < v->data.buffer.size ) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    strncpy((char*)s,(const char*)v->data.buffer.ptr+v->data.buffer.offset,v->data.buffer.size);
    return ErrorCode(ErrorNone);
}

Error Url_set(Url *v, const char *s) {
    CHECK_ERROR(v)
    CHECK_ERROR(s)
    Error e = Url_valid(&v->data);
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

Url Url_new(buffer_t *b, size_t n) {

    Url init = { { {0,0,0}},
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

Url Url_init(Url_t *v) {
    return Url_new(&v, v->size);
}
