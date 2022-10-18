
#include "encoding.h"

ENCODE_COPY(RawJson)
ENCODE_EQUAL(RawJson)

int RawJson_binarySize(const RawJson *v) {
    String s;
    s.data = v->data;
    return String_binarySize(&s);
}

Error RawJson_valid(const Bytes *v) {
    return String_valid(v);
}

Error RawJson_get(const RawJson *v, char *s, size_t slen) {
    CHECK_ERROR(v)

    String str;
    str.data.buffer = v->data.buffer;
    return String_get(&str, s, slen);
}

Error RawJson_set(RawJson *v, const char *s) {
    CHECK_ERROR(v)
    CHECK_ERROR(s)
    String str;
    str.data.buffer = v->data.buffer;
    return String_set(&str, s);
}

RawJson RawJson_new(buffer_t *b, size_t n) {
    RawJson init = { { {0,0,0}}};

    if (b) {
        int sizeNeeded = n;
        if ( (int)b->size - (int)b->offset < sizeNeeded ) {
            return init;
        }
        init.data.buffer.ptr = b->ptr;
        init.data.buffer.offset = b->offset;
        init.data.buffer.size = sizeNeeded;
        b->offset += sizeNeeded;
    }
    return init;
}
