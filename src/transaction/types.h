#pragma once

#include <string.h>  // memmove / strlen
#include <stddef.h>  // size_t
#include <stdint.h>  // uint*_t
#include <encoding/encoding.h>
#define MAX_TX_LEN            510
#define ADDRESS_LEN           20
#define CHECKSUM_LEN          4
#define LITE_ADDRESS_LEN      (ADDRESS_LEN + CHECKSUM_LEN) * 2
#define ACME_LITE_ADDRESS_LEN LITE_ADDRESS_LEN + 5

#define MAX_MEMO_LEN 465  // 510 - ADDRESS_LEN - 2*SIZE(U64) - SIZE(MAX_VARINT)

typedef enum {
    PARSING_OK = 1,
    NONCE_PARSING_ERROR = -1,
    TO_PARSING_ERROR = -2,
    VALUE_PARSING_ERROR = -3,
    MEMO_LENGTH_ERROR = -4,
    MEMO_PARSING_ERROR = -5,
    MEMO_ENCODING_ERROR = -6,
    WRONG_LENGTH_ERROR = -7
} parser_status_e;
