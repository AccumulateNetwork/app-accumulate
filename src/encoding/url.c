
#include <encoding/encoding.h>

ENCODE_COPY(Url)
ENCODE_EQUAL(Url)

int Url_binarySize(const Url *v) {
    String s;
    s.data = v->data;
    return String_binarySize(&s);
}

Error Url_valid(const Bytes *v) {
    return String_valid(v);
}

Error Url_get(const Url *v, char *s, size_t slen) {
    CHECK_ERROR(v)

    String str;
    str.data.buffer = v->data.buffer;
    return String_get(&str, s, slen);
}

Error Url_set(Url *v, const char *s) {
    CHECK_ERROR(v)
    CHECK_ERROR(s)
    String str;
    str.data.buffer = v->data.buffer;
    return String_set(&str, s);
}

Url Url_new(buffer_t *b, size_t n) {
    Url init = {
        {{0, 0, 0}},
    };

    if (b) {
        int sizeNeeded = n;
        if ((int) b->size - (int) b->offset < sizeNeeded) {
            return init;
        }
        init.data.buffer.ptr = b->ptr;
        init.data.buffer.offset = b->offset;
        init.data.buffer.size = sizeNeeded;
        b->offset += sizeNeeded;
    }
    return init;
}
