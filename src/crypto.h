
#pragma once

#include <stdint.h>  // uint*_t

#include "os.h"
#include "cx.h"

/**
 * Derive private key given BIP32 path.
 *
 * @param[out] private_key
 *   Pointer to private key.
 * @param[out] chain_code
 *   Pointer to 32 bytes array for chain code.
 * @param[in]  bip32_path
 *   Pointer to buffer with BIP32 path.
 * @param[in]  bip32_path_len
 *   Number of path in BIP32 path.
 *
 * @return 0 if success, -1 otherwise.
 *
 * @throw INVALID_PARAMETER
 *
 */
int crypto_derive_private_key(cx_ecfp_private_key_t *private_key,
                              const uint32_t *bip32_path,
                              uint8_t bip32_path_len);
/**
 * Initialize public key given private key.
 *
 * @param[in]  private_key
 *   Pointer to private key.
 * @param[out] public_key
 *   Pointer to public key.
 * @param[out] raw_public_key
 *   Pointer to raw public key.
 *
 * @return 0 if success, Error otherwise.
 *
 * @throw INVALID_PARAMETER
 *
 */
Error crypto_init_public_key(cx_ecfp_private_key_t *private_key,
                             cx_ecfp_public_key_t *public_key,
                             uint8_t raw_public_key[static 65],//can be as large is 65 bytes
                             uint8_t *public_key_len,
                             bool compress);
/**
 * Sign message hash in global context.
 *
 * @see G_context.bip32_path, G_context.tx_info.m_hash,
 * G_context.tx_info.signature.
 *
 * @return 0 if success, -1 otherwise.
 *
 * @throw INVALID_PARAMETER
 *
 */
int crypto_sign_message(uint8_t *signature, uint8_t *signature_len, uint8_t *parity);

void crypto_ripemd160(const uint8_t *in, uint16_t inlen, uint8_t out[static 20]);
void crypto_hash160(const uint8_t *in, uint16_t inlen, uint8_t out[static 20]);