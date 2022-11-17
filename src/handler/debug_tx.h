#pragma once

#include <stdint.h>   // uint*_t
#include <stdbool.h>  // bool

#include <common/buffer.h>

/**
 * Handler for DEBUG_TX command. If successfully parse BIP32 path
 * and transaction, sign transaction and send APDU response.
 *
 * @see G_context.bip32_path, G_context.tx_info.raw_transaction,
 * G_context.tx_info.signature and G_context.tx_info.v.
 *
 * @return zero or positive integer if success, negative integer otherwise.
 *
 */
int handler_debug_tx();

