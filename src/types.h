#pragma once

#include <common/bip32.h>
#include <protocol/signatures.h>
#include <protocol/transaction.h>
#include <protocol/unions.h>
#include <stddef.h>  // size_t
#include <stdint.h>  // uint*_t

#include "constants.h"
#include "transaction/types.h"

/**
 * Enumeration for the status of IO.
 */
typedef enum
{
    READY,     /// ready for new event
    RECEIVED,  /// data received
    WAITING    /// waiting
} io_state_e;

/**
 * Enumeration with expected INS of APDU commands.
 */
typedef enum
{
    GET_VERSION = 0x03,            /// version of the application
    GET_APP_NAME = 0x04,           /// name of the application
    GET_PUBLIC_KEY = 0x05,         /// public key of corresponding BIP32 path
    SIGN_TX = 0x06,                /// sign transaction with BIP32 path
    GET_APP_CONFIGURATION = 0x07,  /// get the current configuration settings of the application
} command_e;

/**
 * Structure with fields of APDU command.
 */
typedef struct {
    uint8_t cla;    /// Instruction class
    command_e ins;  /// Instruction code
    uint8_t p1;     /// Instruction parameter 1
    uint8_t p2;     /// Instruction parameter 2
    uint16_t lc;    /// Length of command data
    uint8_t *data;  /// Command data
} command_t;

typedef uint64_t CoinType;
static const CoinType CoinTypeBtc = 0x80000000;
static const CoinType CoinTypeEth = 0x8000003c;
static const CoinType CoinTypeFct = 0x80000083;
static const CoinType CoinTypeAcme = 0x80000119;

/**
 * Enumeration with parsing state.
 */
typedef enum
{
    STATE_NONE,     /// No state
    STATE_PARSED,   /// Transaction data parsed
    STATE_APPROVED  /// Transaction data approved
} state_e;

/**
 * Enumeration with user request type.
 */
typedef enum
{
    CONFIRM_ADDRESS,     /// confirm address derived from public key
    CONFIRM_TRANSACTION  /// confirm transaction information
} request_type_e;

/**
 * Structure for public key context information.
 */
typedef struct {
    uint8_t raw_public_key[65];  /// v, x-coordinate (32), y-coodinate (32)
    uint8_t public_key_length;   /// length of key, compressed / uncompressed
    uint8_t chain_code[32];      /// for public key derivation
    char address_name[MAX_ACME_LITE_ACCOUNT_LEN];
    char lite_account[MAX_ACME_LITE_ACCOUNT_LEN];
    uint8_t hash[32];
    uint8_t hashLength;
} pubkey_ctx_t;

/**
 * Structure for transaction information context.
 */
typedef struct {
    uint8_t memory[ARENA_SIZE];
    uint8_t raw_tx[MAX_TRANSACTION_LEN];  /// raw transaction serialized
    buffer_t arena;
    Signature *signer;
    Transaction *transaction;
    size_t raw_tx_len;          /// length of raw transaction
    uint8_t signing_token[32];  /// blind signing token to compare against system token
    uint8_t metadataHash[32];
    uint8_t initiatorHash[33];           /// initiator hash -> field (1 byte) + hash (32 bytes)
    uint8_t m_hash[32];                  /// transaction / message hash digest
    uint8_t signature[MAX_DER_SIG_LEN];  /// transaction signature encoded in DER
    uint8_t signature_len;               /// length of transaction signature
    uint8_t v;                           /// parity of y-coordinate of R in ECDSA signature
} transaction_ctx_t;

/**
 * Length of the blind signing token
 */
#define BLIND_SIGNING_TOKEN_LENGTH 32

/**
 * Structure for global context.
 */
typedef struct {
    state_e state;  /// state of the context
    union {
        pubkey_ctx_t pk_info;       /// public key context
        transaction_ctx_t tx_info;  /// transaction context
    };
    request_type_e req_type;              /// user request
    uint32_t bip32_path[MAX_BIP32_PATH];  /// BIP32 path
    uint8_t bip32_path_len;               /// length of BIP32 path
} global_ctx_t;

/**
 * Structure for global blind signing context.
 */
typedef struct {
    uint8_t blind_signing_enabled;  /// set to 1 if enabled
} global_settings_ctx_t;
