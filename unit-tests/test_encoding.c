#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmocka.h>

#include "common/buffer.h"
#include <common/encoding.h>

static void test_encoding_bytes32(void **state) {
    (void) state;

    Bytes32 b;
    Error err = Error_init(0);

    Bytes32_init(&b);
    assert_true( err.code == ErrorOk );
    assert_true( b.BinarySize == BinarySizeBytes32 );
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

static void test_encoding_bytes64(void **state) {
    (void) state;

    Bytes64 b;
    Error err = Error_init(0);

    Bytes64_init(&b);
    assert_true( err.code == ErrorOk );
    assert_true( b.BinarySize == BinarySizeBytes64 );
    assert_true( b.len == 64 );

    Bytes64 c = b;

    assert_true( b.Equal(&b, &c) );

    for ( int i = 0; i < 64; ++i ) {
        b.data[i] = i;
    }

    assert_false( b.Equal(&b, &c) );

    //now test the marshaling and unmarshaling.
    uint8_t buffer[64] = {0};

    Bytes bytes = { .data = buffer, .len = sizeof(buffer) };
    err = b.MarshalBinary(&b, &bytes);
    assert_true( err.code == 0);

    err = c.UnmarshalBinary(&c, &bytes);
    assert_true( err.code == 0);

    assert_true( b.Equal(&b, &c));

}

int main() {
    const struct CMUnitTest tests[] = {
                cmocka_unit_test(test_encoding_bytes32),
                cmocka_unit_test(test_encoding_bytes64),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
