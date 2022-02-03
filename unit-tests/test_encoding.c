#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmocka.h>

#include "common/buffer.h"
#include <common/encoding.h>
#include "_enums.h"
#include "_test.h"

static void test_encoding_bytes(void **state) {
    (void) state;

    uint8_t buff1[1024] = {0};
    uint8_t buff2[1024] = {0};

    buffer_t backend = {buff1,sizeof(buff1),0};
    buffer_t primary = {buff2,sizeof(buff2),0};

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


static void test_encoding_struct(void **state) {
    (void) state;

    Bytes32 b;
    Error err = Error_init(0);

    Bytes32_init(&b);
    assert_true( err.code == ErrorOk );
    assert_true( b.BinarySize == Bytes32_binarySize );
    assert_true( b.len == 32 );

    Bytes32 c = b;

    assert_true( b.Equal(&b, &c) );

    for ( int i = 0; i < 32; ++i ) {
        b.data[i] = i;
    }

    assert_false( b.Equal(&b, &c) );

    //now test the marshaling and unmarshaling.
    uint8_t buffer[32] = {0};

    Bytes bytes = { .data = buffer, .len = sizeof(buffer) };
    err = b.MarshalBinary(&b, &bytes);
    assert_true( err.code == 0);

    err = c.UnmarshalBinary(&c, &bytes);
    assert_true( err.code == 0);

    assert_true( b.Equal(&b, &c));
}

//static void test_encoding_bytes64(void **state) {
//    (void) state;

//    Bytes64 b;
//    Error err = Error_init(0);

//    Bytes64_init(&b);
//    assert_true( err.code == ErrorOk );
//    assert_true( b.BinarySize == Bytes64_binarySize );
//    assert_true( b.len == 64 );

//    Bytes64 c = b;

//    assert_true( b.Equal(&b, &c) );

//    for ( int i = 0; i < 64; ++i ) {
//        b.data[i] = i;
//    }

//    assert_false( b.Equal(&b, &c) );

//    //now test the marshaling and unmarshaling.
//    uint8_t buffer[64] = {0};

//    Bytes bytes = { .data = buffer, .len = sizeof(buffer) };
//    err = b.MarshalBinary(&b, &bytes);
//    assert_true( err.code == 0);

//    err = c.UnmarshalBinary(&c, &bytes);
//    assert_true( err.code == 0);

//    assert_true( b.Equal(&b, &c));

//}

int main() {
    const struct CMUnitTest tests[] = {
                        cmocka_unit_test(test_encoding_bytes32),
                        //cmocka_unit_test(test_encoding_bytes64),
                        cmocka_unit_test(test_encoding_bytes),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
