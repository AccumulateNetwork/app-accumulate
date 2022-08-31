#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmocka.h>

#include "common/buffer.h"
#include <common/encoding/encoding.h>
#include <common/sha256.h>
#define ACME_HEADER
//#include "_enums2.h"
#include <common/protocol/enum.h>
#include <common/protocol/types.h>

typedef struct {
   Bytes32 a;
   Bytes64 b;
   String c;
   BigInt d;
   VarInt e;
} test_e; //encoder

test_e init_test_e_from_buffer(buffer_t *buffer) {
    test_e init;
    init.a = Bytes32_new(buffer, 1);
    init.b = Bytes64_new(buffer, 1);
    init.c = String_new(buffer, 16);
    init.d = BigInt_new(buffer);
    init.e = VarInt_new(buffer);
    return init;
}

static void test_encoding_bytes(void **state) {
    (void) state;

    Bytes32_t bt;
    Error err = Error_init(0);

    Bytes32 b = Bytes32_init(&bt);

    //test copy...
    Byte_t ct[32] = {0};

    Error e = sha256(ct,sizeof(ct), ct, sizeof(ct));
    assert_true( e.code == ErrorNone );

    Bytes c = Bytes_init(ct, 32);

    assert_false( Bytes_equal(&b.data, &c) );

    // c has set the size to 32 from b, and then it will increment
    // the offset for d where we want to use another 32 bytes
    Byte_t primary[1024];
    buffer_t buffer = {primary, sizeof(primary), 0 };
    Bytes d = Bytes_new(&buffer, c.buffer.size);

    Bytes_copy(&d, &c);

    assert_true( Bytes_equal(&c, &d) );

    //clear out d
    memset((uint8_t*)(c.buffer.ptr+c.buffer.offset), 0, c.buffer.size);

    assert_false( Bytes_equal(&c, &d) );


    uint8_t marshalerData[1024] = {0};
    buffer_t marshalerBuffer = {marshalerData,sizeof(marshalerData),0};
    Marshaler m = NewMarshaler(&marshalerBuffer);

    int code = marshalerWriteBytes(&m, &d);
    assert_false(IsError(ErrorCode(code)));

    buffer_t enc = marshalerGetEncodedBuffer(&m);
    Unmarshaler unEqualBytesUnmarshaler = NewUnmarshaler(&enc,0);
    code = unmarshalerReadBytesRaw(&unEqualBytesUnmarshaler,&c);

    //should pass unmarshaling
    assert_false( IsError(ErrorCode(code)) );
    //should fail.
    assert_false( Bytes_equal(&d, &c));

    //now try again.
    Unmarshaler equalBytesUnmarshaler = NewUnmarshaler(&enc, 0);
    code = unmarshalerReadBytes(&equalBytesUnmarshaler, &c);
    //should pass unmarshaling
    assert_false( IsError(ErrorCode(code)) );
    //should pass comparison
    assert_true( Bytes_equal(&d, &c));
}

static void test_encoding_varint(void **state) {
    (void) state;
    uint64_t test_uint = 1234;
    int64_t test_int = 1234;

    //test field encoding.
    uint8_t expected_uint[10] = { 0xd2, 0x09,0,0,0,0,0, 0,0, 0 };
    buffer_t expected_uvarint_buffer = {expected_uint, sizeof (expected_uint), 0};
    UVarInt expected_uvarint = UVarInt_new(&expected_uvarint_buffer);

    uint8_t marshalBuffer[1024] = {0};
    buffer_t buffer = { &marshalBuffer, sizeof (marshalBuffer), 0};

    //test marshaler
    Marshaler m = NewMarshaler(&buffer);
    int code = marshalerWriteUVarInt(&m, &expected_uvarint);
    assert_false(IsError(ErrorCode(code)));

    //test unmarshaler
    buffer_t enc = marshalerGetEncodedBuffer(&m);
    Unmarshaler u = NewUnmarshaler(&enc, 0);
    UVarInt test_uvarint_unmarshal = UVarInt_new(0);
    code = unmarshalerReadUVarInt(&u, &test_uvarint_unmarshal );
    assert_false(IsError(ErrorCode(code)));
    assert_true( 2 == uvarint_size(test_uint) );

    //test the varint
    uint8_t expected_int[10] = { 0xa4, 0x13, 0,0,0,0,0,0,0 , 0 };
    buffer_t expected_varint_buffer = {expected_int, sizeof (expected_int), 0};
    VarInt expected_varint = VarInt_new(&expected_varint_buffer);
    m = NewMarshaler(&buffer);
    code = marshalerWriteVarInt(&m, &expected_varint);
    assert_false(IsError(ErrorCode(code)));
    assert_true(code == 2);

    //test the varint unmarshaler
    enc = marshalerGetEncodedBuffer(&m);
    u = NewUnmarshaler(&enc, 0);
    VarInt test_varint_unmarshal = VarInt_new(0);
    code = unmarshalerReadVarInt(&u, &test_varint_unmarshal );
    assert_false(IsError(ErrorCode(code)));
    assert_true( 2 == varint_size(test_int) );
}

#include <common/format.h>

static void test_encoding_bigint(void **state) {
    const char *hex = "000165e2d19bbebe548e2189e84824a90aa900f2d2ede8ff5d65383be3bece06e85f430a07fb170f";
    uint8_t out[1024] = {0};
    int n = hextobin(hex, strlen(hex), out, sizeof(out));
    assert_true(n == strlen(hex)/2);

    const char *bigpi = "314159265358979323846264338327950288419716939937510582097494459";
    uint256_t number;
    assert_true(fromstring256(bigpi, strlen(bigpi), &number) != -1);

    char str[1024] = {0};
    tostring256(&number, 10, str, sizeof(str));
    assert_true(strcmp(bigpi, str) == 0);

    const char *hexpi = "c380755ca7f8336fb62250484a62801dd3098a9e48ece96341bb";

    memset(out, 0, sizeof(out));
    uint256_t bigpi2;

    assert_true(fromhex256(hexpi, strlen(hexpi),&bigpi2) > 0);

    memset(out, 0, sizeof(out));

    int outlen = tobytes256(&bigpi2, out, sizeof(out));
    assert_true(outlen > 0);
    //writeu256BE(&bigpi2, out);

    memset(str, 0, sizeof(str));
    format_hex(out, outlen, str, sizeof(str));
    printf("-> %s\n", str);

    tostring256(&bigpi2, 16,out, sizeof(out));
    printf("%s\n", out);

    printf("bits %d\n", bits256(&bigpi2));

    tostring256(&number, 16,out, sizeof(out));
    printf("%s\n", out);
    assert_true(equal256(&number, &bigpi2));

    buffer_t mempool[1024] = {0};
    buffer_t mempool_buffer = { &mempool, sizeof (mempool), 0};

    uint8_t marshalBuffer[1024] = {0};
    buffer_t buffer = { &marshalBuffer, sizeof (marshalBuffer), 0};

    //test marshaler
    BigInt bi = BigInt_new(&mempool_buffer);
    BigInt_set(&bi, &number);

    Marshaler m = NewMarshaler(&buffer);
    int code = marshalerWriteBigInt(&m, &bi);
    assert_false(IsError(ErrorCode(code)));

    //test unmarshaler
    buffer_t enc = marshalerGetEncodedBuffer(&m);
    Unmarshaler u = NewUnmarshaler(&enc, 0);
    BigInt pi = BigInt_new(0);
    code = unmarshalerReadBigInt(&u, &pi );
    assert_false(IsError(ErrorCode(code)));

    uint256_t readbi;
    BigInt_get(&pi, &readbi);

    assert_true(equal256(&readbi, &number) );

}

int main() {
    const struct CMUnitTest tests[] = {
                        cmocka_unit_test(test_encoding_bytes),
                        cmocka_unit_test(test_encoding_varint),
                        cmocka_unit_test(test_encoding_bigint),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
