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
    //char *apdu_payload = "008b01020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11043b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d450501069ca3e4b4ba3008c4dcfc1b86ccdd0cd7937fcb2619a2735b59f8119a43cd7d396690b5c017bf0400b6016b013b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d45022aa4dd0e234834061b2ec1402b95e7888af941f6d47d3a5d82e15789c47c82c9030b6c65646765722074657374024701030443013b6163633a2f2f6639666562393361313063616632646466313633396336666634353934666262313939633964653963643130636134372f41434d4502043b9aca002036fbe60414509eb11b04b900d8d69191e456fac7b33a74842af7272968c308e5";
    //char *apdu_payload = "0086010202208bb4df5d3604b431f46060ca34f358822be7264df2dbf3c4a5481b0a5fb83ce204366163633a2f2f323235393161323066396666386339386238336338323838653134613131363961663931343337323563343439653630050106f8d6acfac0300886f5e81ad8526894115bb306ff3e06a1c85475a1ddcb4a0558bc3a3848f2afc300a5015e013b6163633a2f2f3232353931613230663966663863393862383363383238386531346131313639616639313433373235633434396536302f41434d4502c90d59ed45e8d0c25f0cd751f7cf66e7a89b2b886b586d2e3fbfde5d6a87e6280243010e02366163633a2f2f323235393161323066396666386339386238336338323838653134613131363961663931343337323563343439653630030203e80480e1eb17";
    char *apdu_payload = "00880108022102f7aa1eb14de438735c026c7cc719db11baf82e47f8fa2c86b55bff92b677eae2043b6163633a2f2f3033323534386230616339313566613963613063313935663339346439356234643464363431346163383061393635352f41434d45050106b96008d792069ec4c8a050be77da3187d1dc6095ce710e0c8ef73db8294cf2d48237f700bf0174013b6163633a2f2f3033323534386230616339313566613963613063313935663339346439356234643464363431346163383061393635352f41434d450248f9fb1100e148a393ca054fb4e5e73fa63f3a0a666df8fb22f7224f9585c37003146274632073656e6420746f6b656e732074657374024701030443013b6163633a2f2f6132376466323065363537396163343732343831663065613931383136356432346266623731336237326231333538352f41434d4502043b9aca00";
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

void test_metadata_signing_hash(void **state) {
    (void) **state;
    (void) **state;
    uint8_t memory[1024] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), 0};

    const char *metadataHashHex = "e4cdb19e50c85630067cdf103e26563e04e2bfe88e739ae7839888b0ef085464";
    uint8_t metadataHashOut[32] = {0};
    hextobin(metadataHashHex, strlen(metadataHashHex),metadataHashOut, 32);
    Signature signer;
    Transaction transaction;
    getTestTransaction(&signer, &transaction, &arena);

    uint8_t txHash[32] = {0};
    int e = transactionHash(&transaction, txHash);
    assert_false(IsErrorCode(e));
    uint8_t hash[32] = {0};
    uint8_t mdhash[32] = {0};
    e = metadataHash(&signer, txHash, hash, mdhash);
    assert_false(IsErrorCode(e));
    assert_memory_equal(hash, mdhash,32);
    assert_false(memcmp(hash, signer._u->TransactionHash.data.buffer.ptr+signer._u->TransactionHash.data.buffer.offset,32));
}

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_hasher),
            cmocka_unit_test(test_initiator),
            cmocka_unit_test(test_transaction_hash),
            cmocka_unit_test(test_metadata_signing_hash)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}

