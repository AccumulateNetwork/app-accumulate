#pragma once

/**
 * Handler for GET_BLIND_SIGNING_TOKEN command that will return a random key that can be passed to
 * SIGN_TX that will sign a transaction without presenting it to the user for confirmation
 *
 * @return zero or positive integer if success, negative integer otherwise.
 *
 */
int handler_get_blind_signing_token();

/**
 * Handler for RESET_BLIND_SIGNING_TOKEN command that will return a random key that can be passed to
 * SIGN_TX that will sign a transaction without presenting it to the user for confirmation
 *
 * @return zero or positive integer if success, negative integer otherwise.
 *
 */
int handler_clear_blind_signing_token();