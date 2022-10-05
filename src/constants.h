#pragma once

#include <bolos_target.h>

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
 * Maximum transaction length (bytes).
 */
#ifdef TARGET_NANOS
#define MAX_DATA_ENTRY 1
#define ARENA_SIZE 512
#else
#define MAX_DATA_ENTRY 10
#define ARENA_SIZE 4096
#endif
#define MAX_SIGNATURE_HEADER_LEN 256

#define MAX_TRANSACTION_LEN 512*MAX_DATA_ENTRY //10270 //510

/**
 * Maximum signature length (bytes).
 */
#define MAX_DER_SIG_LEN 72

/**
 * Maximum signature length (bytes).
 */
#define MAX_ACME_LITE_ACCOUNT_LEN 61

/**
 * Exponent used to convert mBOL to BOL unit (N BOL = N * 10^3 mBOL).
 */
#define EXPONENT_SMALLEST_UNIT 3
