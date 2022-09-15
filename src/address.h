#pragma once

#include <stdint.h>   // uint*_t
#include <stddef.h>   // size_t
#include <stdbool.h>  // bool
#include "common/error.h"
#include "types.h"

/**
 * Convert public key to address.
 *
 * address = Keccak256(public_key)[12:32] (20 bytes)
 *
 * @param[in]  public_key
 *   Pointer to byte buffer with public key.
 *   The public key is represented as 64 bytes with 32 bytes for
 *   each coordinate.
 * @param[out] out
 *   Pointer to output byte buffer for address.
 * @param[in]  out_len
 *   Lenght of output byte buffer.
 *
 * @return true if success, false otherwise.
 *
 */
//bool address_from_pubkey(const uint8_t public_key[static 64], uint8_t *out, size_t out_len);


bool lite_address_from_pubkey(CoinType t, pubkey_ctx_t *publicKey);

bool getEthLiteIdentity(pubkey_ctx_t *publicKey);

bool getBtcLiteIdentity(pubkey_ctx_t *publicKey);

bool getFctLiteAddress(pubkey_ctx_t *publicKey);

bool getLiteAcmeAddress(pubkey_ctx_t *publicKey);

bool getLiteAcmeUrl(const uint8_t public_key[static 64],
                    uint8_t *out, size_t out_len,
                    int8_t *keyName, size_t keyNameLen);

bool getLiteIdentityUrl(const uint8_t *keyHash, uint8_t keyHashLen,
                        int8_t *urlOut, size_t urlOutLen);
//
//Error resolvePublicKey( CoinType type, pubkey_ctx_t *publicKey,
//                       uint8_t *out, size_t *inoutlen);