#pragma once

#include <stdint.h>   // uint*_t
#include <stdbool.h>  // bool

#include "types.h"
#include <common/protocol/signatures.h>
#include <common/protocol/transaction.h>

int readSignature(Unmarshaler *m, Signature *v);
int readSignatureTypeUnion(Unmarshaler *m, SignatureTypeUnion *v);
int readTransactionHeader(Unmarshaler *m, TransactionHeader *v) ;
int readTokenRecipient(Unmarshaler *m, TokenRecipient *v);
int readSendTokens(Unmarshaler *m, SendTokens *v);
int readAddCredits(Unmarshaler *m, AddCredits *v);
int readTransactionBody(Unmarshaler *m, TransactionBody *v) ;
int readTransactionTypeHeader(Unmarshaler *m, TransactionType *type);
int readTransaction(Unmarshaler *m, Transaction *v);

int initiatorHash(Signature *s, uint8_t initiator[static 32]);
int transactionHash(Transaction *s, uint8_t hash[static 32]);
int parse_transaction(uint8_t *raw_tx, uint16_t raw_tx_len, Signature *signer, Transaction *transaction, buffer_t *arena);
