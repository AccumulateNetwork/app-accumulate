#pragma once

#include <stdbool.h>  // bool

/**
 * Action for public key validation and export.
 *
 * @param[in] choice
 *   User choice (either approved or rejectd).
 *
 */
void ui_action_validate_pubkey(bool choice);

/**
 * Action for transaction information validation.
 *
 * @param[in] choice
 *   User choice (either approved or rejectd).
 *
 */
void ui_action_validate_transaction(bool choice);
void ui_action_validate_transaction_hash(bool choice);

void ui_action_enable_blind_signing(bool choice);