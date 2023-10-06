#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

extern "C" {
#include "constants.h"
#include "common/buffer.h"
#include <encoding/encoding.h>
#include <common/sha256.h>
#include <protocol/enum.h>
#include <protocol/transaction.h>
#include <protocol/signatures.h>
#include <transaction/utils.h>
#include <common/error.h>
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    buffer_t buf = {.ptr = data, .size = size, .offset = 0};

    uint8_t memory[ARENA_SIZE] = {0};
    buffer_t arena = {.ptr = memory, .size = sizeof(memory), .offset = 0};

    Unmarshaler envUnmarshaler = {.buffer.ptr = data,
                                  .buffer.size = size,
                                  .buffer.offset = 0,
                                  .mempool = &arena};
    Envelope env;
    explicit_bzero(&env, sizeof(env));

    int e = readEnvelope(&envUnmarshaler, &env);
    if (IsError(ErrorCode(e))) {
        return e;
    }

    return 0;
}
