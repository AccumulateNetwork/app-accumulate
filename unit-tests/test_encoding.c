#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmocka.h>

#include "common/buffer.h"
#include <common/encoding.h>
#define ACME_HEADER
#include "_enums2.h"
#include <common/protocol/enum.h>


typedef struct {
   Bytes32_t a;
   Bytes64_t b;
   String_t c;
   BigInt_t d;
   VarInt_t e;
} test_t;

typedef struct {
   Bytes32 a;
   Bytes64 b;
   String c;
   BigInt d;
   VarInt e;
} test_e; //encoder

test_e Test_init(test_t *t) {
    test_e init;
    init.a = Bytes32_init(&t->a);
    init.b = Bytes64_init(&t->b);
    init.c = String_init(&t->c);
    init.d = BigInt_init(&t->d);
    init.e = VarInt_init(&t->e);
    return init;
}

static void test_encoding_struct(void **state) {
    uint8_t backbuff[1024] = {0};

    char str[32] = {0};

    test_t test;
    test.a = memset(test.a, 0, sizeof(a));
    test.b = memset(test.b, 0, sizeof(b));
    test.c.offset = 0;
    test.c.ptr = str;
    test.c.size = sizeof(str);
    zero256(test.d);
    e = 0;

    Bytes_t buffer = {backbuff, sizeof(backbuff), 0};
    Bytes b = Bytes_init(&buffer);

}
static void test_encoding_bytes(void **state) {
    (void) state;

    Bytes32 b;
    Error err = Error_init(0);

    Bytes32_init(&b,&backend);

    //test copy...
    Bytes c;
    Bytes_init(&c, &primary, b.data.buffer.size);

    c.Copy(&c,&b.data);
    assert_true( c.Equal(&b.data, &c) );

    // c has set the size to 32 from b, and then it will increment
    // the offset for d where we want to use another 32 bytes
    Bytes d;
    Bytes_init(&d, &primary, c.buffer.size);

    c.Copy(&c, &d);
    c.Copy(&d, &c);

    assert_true( d.Equal(&c, &d) );

    for ( uint8_t i = 0; i < d.buffer.size; ++i ) {
        memcpy((uint8_t*)(d.buffer.ptr+d.buffer.offset),&i, sizeof(i));
    }

    assert_false( d.Equal(&c, &d) );


    uint8_t marshalerData[1024] = {0};
    buffer_t marshalerBuffer = {marshalerData,sizeof(marshalerData),0};
    Marshaler bytes = Marshaler_init(0,&marshalerBuffer);

    err = d.MarshalBinary(&d, &bytes);
    assert_true( err.code == 0);

    //now test the unmarshaling.
    //clear the buffer of the primary
    memset(buff2,0, sizeof(buff2));

    err = c.UnmarshalBinary(&c, &bytes);

    assert_true( err.code == ErrorNone);

    //now test to see if the orig data matches.
    assert_true( d.Equal(&b.data, &d));
}

int main() {
    const struct CMUnitTest tests[] = {
                        cmocka_unit_test(test_encoding_bytes),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
