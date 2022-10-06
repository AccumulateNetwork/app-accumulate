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
#define MAX_DATA_ENTRY 1 //the nano s can only support smaller transactions
#else
#define MAX_DATA_ENTRY 20+10 //accumulate accepts a max size 20kb transaction + padding for arena
#endif

#define MAX_TRANSACTION_LEN 1024*MAX_DATA_ENTRY //10270 //510

/**
 * Maximum signature length (bytes).
 */
#define MAX_DER_SIG_LEN 65

/**
 * Maximum signature length (bytes).
 */
#define MAX_ACME_LITE_ACCOUNT_LEN 65

/**
 * Exponent used to convert mBOL to BOL unit (N BOL = N * 10^3 mBOL).
 */
#define EXPONENT_SMALLEST_UNIT 3
