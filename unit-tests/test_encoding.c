#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cmocka.h>

#include "common/buffer.h"
#include <encoding/encoding.h>
#include <common/sha256.h>
#include <protocol/enum.h>
#include <protocol/transaction.h>
#include <protocol/signatures.h>
#include <transaction/utils.h>

#define WANT_DEBUG_TX_CODE 0

static void test_encoding_apdu(void **state) {
    UNUSED(state);

    char *apdu_payload = "008b01020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11043b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d450501069ca3e4b4ba3008c4dcfc1b86ccdd0cd7937fcb2619a2735b59f8119a43cd7d396690b5c017bf0400b6016b013b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d45022aa4dd0e234834061b2ec1402b95e7888af941f6d47d3a5d82e15789c47c82c9030b6c65646765722074657374024701030443013b6163633a2f2f6639666562393361313063616632646466313633396336666634353934666262313939633964653963643130636134372f41434d4502043b9aca002036fbe60414509eb11b04b900d8d69191e456fac7b33a74842af7272968c308e5";
    uint8_t raw_tx[1024] = {0};
    hextobin(apdu_payload, (int)strlen(apdu_payload), raw_tx, sizeof(raw_tx));

#if WANT_DEBUG_TX_CODE
    printf("G_context.tx_info.raw_tx_len = 0;\n");
    for ( int i = 0; i < strlen(apdu_payload)/2; i++) {
        printf("G_context.tx_info.raw_tx[G_context.tx_info.raw_tx_len++] = 0x%x;  ",raw_tx[i]);
        if ( i % 20 == 0 ) {
            printf("\n");
        }
    }
    printf("//%d\n",raw_tx_len);
#endif

    int raw_tx_len = (int)strlen(apdu_payload)/2;
    // we have received all the APDU's so let's parse and sign
    buffer_t arena = {.ptr = raw_tx + raw_tx_len, .size = sizeof(raw_tx) - raw_tx_len, 0};

    Signature signer;
    Transaction transaction;
    int e = parse_transaction(raw_tx, raw_tx_len, &signer, &transaction, &arena);
    assert_false(IsError(ErrorCode(e)));
}

static void test_encoding_envelope(void **state) {
    UNUSED(state);

    char *addCreditsEnv = "016c01020220229c50b909dd57a40086670e4f258824d622f9407b2518422e4ef37879643120041d6163633a2f2f6c6974652d746f6b656e2d6163636f756e742e61636d65050106d285d8cc04089fd8eab83fc71d96e16b7d9f71328ba9178122e97a06199e8ee57417b3569b2b035e0140011d6163633a2f2f6c6974652d746f6b656e2d6163636f756e742e61636d6502e91600a1d0afe20619d924aaeb2171bc1f8d20a3ad9baa2212364cbb95f09cef021a010e02136163633a2f2f6164692e61636d652f70616765030164";
    uint8_t envelope[1024] = {0};
    hextobin(addCreditsEnv, (int)strlen(addCreditsEnv), envelope, sizeof(envelope));

    uint8_t arena[1024] = {0};

    memset(&arena, 0, sizeof(arena));
    buffer_t mempool = {arena,sizeof(arena), 0};
    buffer_t envbuffer = {envelope, sizeof(envelope), 0};
    Unmarshaler um = NewUnmarshaler(&envbuffer,&mempool);
    struct Envelope e;

    int n = readEnvelope(&um, &e);
    assert_false(IsError(ErrorCode(n)));
}
static void test_encoding_transaction(void **state) {
    UNUSED(state);


    //PreSignature: {"type":"ed25519","publicKey":"e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11","signer":"acc://c6a629f9a65bf21159c5dfbffbc868ec3ae61ce4651108ec/ACME","signerVersion":1,"timestamp":1664460962464,"transactionHash":"2e1a5959275faaf81dadecbc7c1b27ae43f06793ff45d514f45a3afc77bd0dfd"}
    char *PreSignature = "01020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11043b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d45050106a0f5eaccb830082e1a5959275faaf81dadecbc7c1b27ae43f06793ff45d514f45a3afc77bd0dfd";
    char *PreSignature2 = "01020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11043b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d450501068489f5adba3008981c8ae4417483e896ab9004e75102dd3c2eebe755937ec6e17b9d83f4044895";
    //Transaction: {"header":{"principal":"acc://c6a629f9a65bf21159c5dfbffbc868ec3ae61ce4651108ec/ACME","initiator":"cf45be0d838a5f2a1a9801b794769b95e5657bebd23de07caa6f81f4cdd2d49f","memo":"ledger test"},"body":{"type":"sendTokens","hash":"0000000000000000000000000000000000000000000000000000000000000000","to":[{"url":"acc://f9feb93a10caf2ddf1639c6ff4594fbb199c9de9cd10ca47/ACME","amount":"1000000000"}]}}
    char *Transaction = "016b013b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d4502cf45be0d838a5f2a1a9801b794769b95e5657bebd23de07caa6f81f4cdd2d49f030b6c65646765722074657374024701030443013b6163633a2f2f6639666562393361313063616632646466313633396336666634353934666262313939633964653963643130636134372f41434d4502043b9aca00";
    //char *TransactionHash = "421ed18da7d2bcf31cd58f9479ce2e7c5c316ecf72ca466c8f8b3e094f964fc7";

    uint8_t transaction[1024] = {0};
    hextobin(Transaction, (int)strlen(Transaction), transaction, sizeof(transaction));

    uint8_t arena[1024] = {0};

    memset(&arena, 0, sizeof(arena));
    buffer_t mempool = {arena,sizeof(arena), 0};
    buffer_t txbuffer = {transaction, sizeof(transaction), 0};
    Unmarshaler um = NewUnmarshaler(&txbuffer,&mempool);
    struct Transaction t;
    int n = readTransaction(&um, &t);
    assert_false(IsError(ErrorCode(n)));

    int expectedLen = (int)strlen(Transaction)/2;
    assert_true(expectedLen == n);

    //now test out the Signature processor
    uint8_t preSignature[1024] = {0};
    hextobin(PreSignature2, (int)strlen(PreSignature), preSignature, sizeof(preSignature));

    buffer_t sigbuffer = { preSignature, sizeof(preSignature), 0 };
    um = NewUnmarshaler(&sigbuffer, &mempool);
    //ED25519Signature ed;
    Signature s;// = {._ED25519Signature = &ed };

    n = readSignature(&um, &s);
    assert_false(IsError(ErrorCode(n)));

    expectedLen = (int)strlen(PreSignature)/2;
    assert_true(expectedLen == n);

}

static void test_encoding_bytes(void **state) {
    (void) state;

    Bytes32_t bt;

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

    uint8_t arena[1024] = {0};
    buffer_t mempool = {arena,sizeof(arena), 0};
    buffer_t enc = marshalerGetEncodedBuffer(&m);
    Unmarshaler unEqualBytesUnmarshaler = NewUnmarshaler(&enc,&mempool);
    code = unmarshalerReadBytesRaw(&unEqualBytesUnmarshaler,&c, c.buffer.size-c.buffer.offset);

    //should pass unmarshaling
    assert_false( IsError(ErrorCode(code)) );
    //should fail.
    assert_false( Bytes_equal(&d, &c));

    //now try again.
    Unmarshaler equalBytesUnmarshaler = NewUnmarshaler(&enc, &mempool);
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
    buffer_t buffer = { marshalBuffer, sizeof (marshalBuffer), 0};

    //test marshaler
    Marshaler m = NewMarshaler(&buffer);
    int code = marshalerWriteUVarInt(&m, &expected_uvarint);
    assert_false(IsError(ErrorCode(code)));

    uint8_t arena[1024] = {0};
    buffer_t mempool = {arena,sizeof(arena), 0};
    //test unmarshaler
    buffer_t enc = marshalerGetEncodedBuffer(&m);
    Unmarshaler u = NewUnmarshaler(&enc, &mempool);
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
    u = NewUnmarshaler(&enc, &mempool);
    VarInt test_varint_unmarshal = VarInt_new(0);
    code = unmarshalerReadVarInt(&u, &test_varint_unmarshal );
    assert_false(IsError(ErrorCode(code)));
    assert_true( 2 == varint_size(test_int) );
}

#include <common/format.h>

static void test_encoding_bigint(void **state) {
    UNUSED(state);

    const char *hex = "000165e2d19bbebe548e2189e84824a90aa900f2d2ede8ff5d65383be3bece06e85f430a07fb170f";
    uint8_t out[1024] = {0};
    int n = hextobin(hex, (int)strlen(hex), out, sizeof(out));
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

    int outlen = tobytes256(&bigpi2,(uint8_t*) out, sizeof(out));
    assert_true(outlen > 0);
    //writeu256BE(&bigpi2, out);

    memset(str, 0, sizeof(str));
    format_hex(out, outlen, str, sizeof(str));
    printf("-> %s\n", str);

    tostring256(&bigpi2, 16,(char *)out, sizeof(out));
    printf("%s\n", out);

    printf("bits %d\n", bits256(&bigpi2));

    tostring256(&number, 16,(char*)out, sizeof(out));
    printf("%s\n", out);
    assert_true(equal256(&number, &bigpi2));

    uint8_t arena[1024] = {0};
    buffer_t mempool = { arena, sizeof (arena), 0};

    uint8_t marshalBuffer[1024] = {0};
    buffer_t buffer = { marshalBuffer, sizeof (marshalBuffer), 0};

    //test marshaler
    BigInt bi = BigInt_new(&mempool);
    BigInt_set(&bi, &number);

    Marshaler m = NewMarshaler(&buffer);
    int code = marshalerWriteBigInt(&m, &bi);
    assert_false(IsError(ErrorCode(code)));

    //test unmarshaler
    buffer_t enc = marshalerGetEncodedBuffer(&m);

    Unmarshaler u = NewUnmarshaler(&enc, &mempool);
    BigInt pi = BigInt_new(0);
    code = unmarshalerReadBigInt(&u, &pi );
    assert_false(IsError(ErrorCode(code)));

    uint256_t readbi;
    BigInt_get(&pi, &readbi);

    assert_true(equal256(&readbi, &number) );

}

static void test_encoding_strings(void **state) {
    UNUSED(state);
    uint8_t marshalBuffer[1024] = {0};
    buffer_t buffer = { marshalBuffer, sizeof (marshalBuffer), 0};

    const char *expected_string = "the quick brown fox jumps over the lazy dog";

    char sbuf[256] = {0};

    buffer_t stringbuf = { (uint8_t*)sbuf, sizeof(sbuf), 0};
    String s = String_new(&stringbuf,sizeof(sbuf));

    String_set(&s, expected_string);
    //test marshaler
    Marshaler m = NewMarshaler(&buffer);
    int code = marshalerWriteString(&m, &s);
    assert_false(IsError(ErrorCode(code)));

    //test unmarshaler
    buffer_t enc = marshalerGetEncodedBuffer(&m);

    uint8_t arena[1024] = {0};
    buffer_t mempool = {arena,sizeof(arena), 0};
    Unmarshaler u = NewUnmarshaler(&enc, &mempool);
    String test_string_unmarshal = String_new(0,0);
    code = unmarshalerReadString(&u, &test_string_unmarshal );
    assert_false(IsError(ErrorCode(code)));

    String_get(&test_string_unmarshal, sbuf, sizeof(sbuf) );
    assert_true( strcmp(sbuf, expected_string) == 0 );


}

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    const struct CMUnitTest tests[] = {
                        cmocka_unit_test(test_encoding_bytes),
                        cmocka_unit_test(test_encoding_varint),
                        cmocka_unit_test(test_encoding_bigint),
                        cmocka_unit_test(test_encoding_strings),
                        cmocka_unit_test(test_encoding_apdu),
                        cmocka_unit_test(test_encoding_transaction),
                        cmocka_unit_test(test_encoding_envelope)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
