#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cmocka.h>
#include "common/hasher.h"
#include "common/format.h"
#include "common/sha256.h"
#include "transaction/utils.h"

typedef struct Data {
    char *entry;
} Data;

static void test_hasher(void **state) {
    (void) state;

    Data data[] = {
        "test data entry",
        "extid 0",
        "extid 1",
        "extid 2",
        "extid 3",
        "extid 4",
        "extid 5",
        "extid 6",
        "extid 7",
        "extid 8",
        "extid 9",
    };
//    de.Data = append(de.Data, []byte("test data entry"))
//    for i := 0; i < 10; i++ {
//        de.Data = append(de.Data, []byte(fmt.Sprintf("extid %d", i)))
//    }

    const char *expectedHashHex = "29f613df53d1e38dcfea87b2582985cae5265699ef8fc5c500b0bee8f32974ed";
    uint8_t expectedHash[32];
    hextobin(expectedHashHex, strlen(expectedHashHex), expectedHash, sizeof (expectedHash));

    MerkleState ms;
    MerkleStateInit(&ms);

    for ( int i = 0; i < sizeof(data)/sizeof(Data); i++ ) {
        uint8_t hash[32] = {0};
        sha256(data[i].entry, strlen(data[i].entry), hash, sizeof(hash));
        int e = AddToMerkleTree(&ms,hash);
        assert_false(IsErrorCode(e));
        printf("%x\n", hash);
    }

    uint8_t root[32] = {0};
    MerkleDAGRoot(&ms, root);
    char mdroot[65];
    format_hex(root,32, mdroot,sizeof (mdroot));

    assert_string_equal(mdroot, expectedHashHex);
}
void getTestTransaction(Signature *signer, Transaction *transaction, buffer_t *arena) {
    char *apdu_payload = "008b01020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11043b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d450501069ca3e4b4ba3008c4dcfc1b86ccdd0cd7937fcb2619a2735b59f8119a43cd7d396690b5c017bf0400b6016b013b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d45022aa4dd0e234834061b2ec1402b95e7888af941f6d47d3a5d82e15789c47c82c9030b6c65646765722074657374024701030443013b6163633a2f2f6639666562393361313063616632646466313633396336666634353934666262313939633964653963643130636134372f41434d4502043b9aca002036fbe60414509eb11b04b900d8d69191e456fac7b33a74842af7272968c308e5";

    uint8_t *raw_tx = arena->ptr + arena->offset;
    hextobin(apdu_payload, strlen(apdu_payload), raw_tx,
             arena->size - arena->offset);

    int raw_tx_len = strlen(apdu_payload)/2;
    // we have received all the APDU's so let's parse and sign
    arena->offset += raw_tx_len;

    uint8_t hash[32] = {0};
    int e = parse_transaction(raw_tx, raw_tx_len, signer, transaction, arena);
    assert_false(IsError(ErrorCode(e)));

}

static void test_initiator(void **state) {
    (void)state;
    uint8_t memory[1024] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), 0};

    Signature signer;
    Transaction transaction;
    getTestTransaction(&signer, &transaction, &arena);

    uint8_t hash[32] = {0};
    //extract the initiator
    Bytes initiator = {.buffer.ptr = hash, .buffer.size = sizeof(hash), .buffer.offset = 0 };
    Error err = Bytes32_get(&transaction.Header.Initiator, &initiator);
    assert_false(IsError(err));

    char output[256] = {0};
    format_hex(signer._u->PublicKey.buffer.ptr+signer._u->PublicKey.buffer.offset, signer._u->PublicKey.buffer.size - signer._u->PublicKey.buffer.offset,
    output, sizeof(output));

    printf("%s\n", output);

    Url_get(&signer._u->Signer, output, sizeof(output));
    printf("%s\n", output);

    uint64_t var = 0;
    UVarInt_get(&signer._u->SignerVersion, &var);

    printf("%ld\n", var);
    UVarInt_get(&signer._u->Timestamp, &var);

    printf("%ld\n", var);


    format_hex(transaction.Header.Initiator.data.buffer.ptr+transaction.Header.Initiator.data.buffer.offset,
               transaction.Header.Initiator.data.buffer.size - transaction.Header.Initiator.data.buffer.offset,
               output, sizeof(output));

    printf("internal %s\n", output);

               uint8_t computedHash[32] = {0};
    int e = initiatorHash(&signer, computedHash);
    assert_false(IsErrorCode(e));

    format_hex(computedHash, sizeof(computedHash),
               output, sizeof(output));

    printf("computed %s\n", output);

    assert_memory_equal(hash, computedHash, 32);
}

void test_transaction_hash(void **state) {
    (void) **state;
    uint8_t memory[1024] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), 0};

    Signature signer;
    Transaction transaction;
    getTestTransaction(&signer, &transaction, &arena);

    uint8_t hash[32] = {0};
    int e = transactionHash(&transaction, hash);
    assert_false(IsErrorCode(e));
    assert_false(memcmp(hash, signer._u->TransactionHash.data.buffer.ptr+signer._u->TransactionHash.data.buffer.offset,32));
}

int main() {
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_hasher),
                                        cmocka_unit_test(test_initiator),
                                       cmocka_unit_test(test_transaction_hash)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}
