#pragma once
//#if !defined(__x86_64__)
#include <bolos_target.h>
//#endif

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
#define MAX_DATA_ENTRY 2 //accumulate accepts a max size 20kb transaction + padding for arena
#endif

#define MAX_TRANSACTION_LEN 512*MAX_DATA_ENTRY //10270 //510

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

#define ACME_PRECISION 8
#define CREDITS_PRECISION 4