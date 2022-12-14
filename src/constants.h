#pragma once
#if !defined(__x86_64__)
#include <bolos_target.h>
#endif

/**
 * Instruction class of the Accumulate application.
 */
#define CLA 0xE0

/**
 * Length of APPNAME variable in the Makefile.
 */
#define APPNAME_LEN (sizeof(APPNAME) - 1)

/**
 * Maximum length of MAJOR_VERSION || MINOR_VERSION || PATCH_VERSION.
 */
#define APPVERSION_LEN 3

/**
 * Maximum length of application name.
 */
#define MAX_APPNAME_LEN 64

/**
 * Maximum length of address prefix.
 */
#define MAX_PREFIX_LENGTH 8

/**
 * Maximum length of hash.
 */
#define MAX_HASH_LENGTH 32 + 16  // 32 bytes + 16 multi-hash padding

/**
 * Maximum transaction length (bytes).
 */
#ifdef TARGET_NANOS
#define MAX_DATA_ENTRY 1  // the nano s can only support smaller transactions
#define ARENA_SIZE     512
#else
#define MAX_DATA_ENTRY 5     // allow 20kb for transaction
#define ARENA_SIZE     4096  // arena mempool size
#endif

#define INITIATOR_FIELD_INDEX 1

#define MAX_TRANSACTION_LEN ARENA_SIZE* MAX_DATA_ENTRY  // 10270 nano s+ and nano x / 512 nanos

/**
 * Maximum signature length (bytes).
 */
#define MAX_DER_SIG_LEN 72

/**
 * Maximum signature length (bytes).
 */
#define MAX_ACME_LITE_ACCOUNT_LEN 65

/**
 * Exponent used to convert mBOL to BOL unit (N BOL = N * 10^3 mBOL).
 */
#define EXPONENT_SMALLEST_UNIT 3

#define ACME_PRECISION        8
#define CREDITS_PRECISION     2
#define ORACLE_PRECISION      4
#define CREDITS_PER_FIAT_UNIT 10000
