#pragma once

#include <stdbool.h>  // bool

#include "display.h"
#include "display_transaction.h"
#include "globals.h"
#include "sw.h"
#include "ux.h"

/**
 * Callback to reuse action with approve/reject in step FLOW.
 */
typedef void (*action_validate_cb)(bool);

/**
 * Display address on the device and ask confirmation to export.
 *
 * @return 0 if success, negative integer otherwise.
 *
 */
int ui_display_address(void);


/**
 * Sets a blind signing key on the device if enabled.
 *
 * @return 0 if success, negative integer otherwise.
 *
 */
int ui_display_blind_signing_enable(void);

/**
 * Display transaction information on the device and ask confirmation to sign.
 *
 * @return 0 if success, negative integer otherwise.
 *
 */
int ui_display_transaction(void);

extern const ux_flow_step_t* const ux_dynamic_display_flow[];
extern action_validate_cb g_validate_callback;
extern char g_welcome[32];
extern int g_HaveMemoField;
