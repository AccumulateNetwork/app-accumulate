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

#define ARENA_BUFFER 10240

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
void getTestTransaction(Signature **signer, Transaction **transaction, buffer_t *arena) {
    char *apdu_payload = "016201020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec1104136163633a2f2f6164692e61636d652f41434d45050106d285d8cc0408a76432672cd7834eb26873a33d3e00a350c5a9a3aff9b7cc50637db4931e4b470358013601136163633a2f2f6164692e61636d652f41434d450284e032fba8a5456f631c822a2b2466c18b3fa7804330ab87088ed6e30d690505021e0103041a01156163633a2f2f6f746865722e61636d652f41434d45020164";

    uint8_t *raw_tx = arena->ptr + arena->offset;
    hextobin(apdu_payload, strlen(apdu_payload), raw_tx,
             arena->size - arena->offset);

    int raw_tx_len = strlen(apdu_payload)/2;
    // we have received all the APDU's so let's parse and sign
    arena->offset += raw_tx_len;
    Envelope env;
    explicit_bzero(&env, sizeof(env));
    Unmarshaler envUnmarshaler = {.buffer.ptr = raw_tx,
            .buffer.size = raw_tx_len,
            .buffer.offset = 0,
            .mempool = arena};
    int e = readEnvelope(&envUnmarshaler, &env);

    assert_false(IsError(ErrorCode(e)));

    assert_true(env.Signatures_length == 1);

    //because env.Signatures and env.Transaction are allocated from our unmarshaling memory pool, the pointer assignment is ok...
    *signer = env.Signatures;

    assert_true(env.Transaction_length == 1);
    *transaction = env.Transaction;
}

static void test_initiator(void **state) {
    (void)state;
    uint8_t memory[ARENA_BUFFER] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), 0};

    Signature *signer = NULL;
    Transaction *transaction = NULL;
    getTestTransaction(&signer, &transaction, &arena);

    uint8_t hash[32] = {0};
    //extract the initiator
    Bytes initiator = {.buffer.ptr = hash, .buffer.size = sizeof(hash), .buffer.offset = 0 };
    Error err = Bytes32_get(&transaction->Header.Initiator, &initiator);
    assert_false(IsError(err));

    char output[256] = {0};
    format_hex(signer->_u->PublicKey.buffer.ptr+signer->_u->PublicKey.buffer.offset, signer->_u->PublicKey.buffer.size - signer->_u->PublicKey.buffer.offset,
    output, sizeof(output));

    printf("%s\n", output);

    Url_get(&signer->_u->Signer, output, sizeof(output));
    printf("%s\n", output);

    uint64_t var = 0;
    UVarInt_get(&signer->_u->SignerVersion, &var);

    printf("%ld\n", var);
    UVarInt_get(&signer->_u->Timestamp, &var);

    printf("%ld\n", var);


    format_hex(transaction->Header.Initiator.data.buffer.ptr+transaction->Header.Initiator.data.buffer.offset,
               transaction->Header.Initiator.data.buffer.size - transaction->Header.Initiator.data.buffer.offset,
               output, sizeof(output));

    printf("internal %s\n", output);

               uint8_t computedHash[32] = {0};
    int e = initiatorHash(signer, computedHash);
    assert_false(IsErrorCode(e));

    format_hex(computedHash, sizeof(computedHash),
               output, sizeof(output));

    printf("computed %s\n", output);

    assert_memory_equal(hash, computedHash, 32);
}

void test_transaction_hash(void **state) {
    (void) **state;
    uint8_t memory[ARENA_BUFFER] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), 0};

    Signature *signer = NULL;
    Transaction *transaction = NULL;
    getTestTransaction(&signer, &transaction, &arena);

    uint8_t hash[32] = {0};
    int e = transactionHash(transaction, hash);
    assert_false(IsErrorCode(e));
    assert_false(memcmp(hash, signer->_u->TransactionHash.data.buffer.ptr+signer->_u->TransactionHash.data.buffer.offset,32));

}

void test_metadata_signing_hash(void **state) {
    (void) **state;
    (void) **state;
    uint8_t memory[ARENA_BUFFER] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), 0};

    const char *metadataHashHex = "84e032fba8a5456f631c822a2b2466c18b3fa7804330ab87088ed6e30d690505";//"e4cdb19e50c85630067cdf103e26563e04e2bfe88e739ae7839888b0ef085464";
    uint8_t metadataHashOut[32] = {0};
    hextobin(metadataHashHex, strlen(metadataHashHex),metadataHashOut, 32);
    Signature *signer = NULL;
    Transaction *transaction = NULL;
    getTestTransaction(&signer, &transaction, &arena);

    uint8_t txHash[32] = {0};
    int e = transactionHash(transaction, txHash);
    assert_false(IsErrorCode(e));
    uint8_t comparisonHash[32] = {0};
    memmove(comparisonHash, signer->_u->TransactionHash.data.buffer.ptr+signer->_u->TransactionHash.data.buffer.offset,32);
    assert_memory_equal(txHash, comparisonHash, 32);

    uint8_t hash[32] = {0};
    uint8_t mdhash[32] = {0};
    e = metadataHash(signer, txHash, hash, mdhash);
    assert_false(IsErrorCode(e));

    int8_t output[1024] = {0};

    format_hex(mdhash, sizeof(mdhash),
               output, sizeof(output));

    printf("mdhash%s\n", output);
    assert_memory_equal(mdhash, metadataHashOut, 32);
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

