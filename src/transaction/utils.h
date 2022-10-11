#pragma once

#include <stdint.h>   // uint*_t
#include <stdbool.h>  // bool

#include "types.h"
#include <common/protocol/signatures.h>
#include <common/protocol/transaction.h>


/**
 * Check if memo is encoded using ASCII characters.
 *
 * @param[in] memo
 *   Pointer to input byte buffer.
 * @param[in] memo_len
 *   Lenght of input byte buffer.
 *
 * @return true if success, false otherwise.
 *
 */
bool transaction_utils_check_encoding(const uint8_t *memo, uint64_t memo_len);

/**
 * Format memo as string.
 *
 * @param[in]  memo
 *   Pointer to input byte buffer.
 * @param[in]  memo_len
 *   Lenght of input byte buffer.
 * @param[out] dst
 *   Pointer to output string.
 * @param[in]  dst_len
 *   Lenght of output string.
 *
 * @return true if success, false otherwise.
 *
 */
bool transaction_utils_format_memo(const uint8_t *memo,
                                   uint64_t memo_len,
                                   char *dst,
                                   uint64_t dst_len);

int readSignature(Unmarshaler *m, Signature *v);
int readSignatureTypeUnion(Unmarshaler *m, SignatureTypeUnion *v);
int readTransactionHeader(Unmarshaler *m, TransactionHeader *v) ;
int readTokenRecipient(Unmarshaler *m, TokenRecipient *v);
int readSendTokens(Unmarshaler *m, SendTokens *v);
int readAddCredits(Unmarshaler *m, AddCredits *v);
int readTransactionBody(Unmarshaler *m, TransactionBody *v) ;
int readTransactionTypeHeader(Unmarshaler *m, TransactionType *type);
int readTransaction(Unmarshaler *m, Transaction *v);

int parse_transaction(uint8_t *raw_tx, uint16_t raw_tx_len, Signature *signer, Transaction *transaction, buffer_t *arena,
                      uint8_t *hash, uint8_t hash_len);
