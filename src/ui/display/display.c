/*****************************************************************************
 *   Accumulate Ledger Wallet
 *   (c) 2022 DefiDevs, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#pragma GCC diagnostic ignored "-Wformat-invalid-specifier"  // snprintf
#pragma GCC diagnostic ignored "-Wformat-extra-args"         // snprintf

#include "display.h"

#include <stdbool.h>  // bool
#include <string.h>   // memset

#include "address.h"
#include "common/bip32.h"
#include "common/format.h"
#include "constants.h"
#include "globals.h"
#include "glyphs.h"
#include "io.h"
#include "os.h"
#include "sw.h"
#include "transaction/types.h"
#include "ui/action/validate.h"
#include "ui/display/display_address.h"
#include "ui/display/display_transaction.h"
#include "ui/dynamic_display.h"
#include "ux.h"

action_validate_cb g_validate_callback;
char g_welcome[32];
int g_HaveMemoField;

// Step with approve button
UX_STEP_CB(ux_display_approve_step,
           pb,
           (*g_validate_callback)(true),
           {
               &C_icon_validate_14,
               "Approve",
           });
// Step with reject button
UX_STEP_CB(ux_display_reject_step,
           pb,
           (*g_validate_callback)(false),
           {
               &C_icon_crossmark,
               "Reject",
           });

// Step with icon and text
UX_STEP_NOCB(ux_display_review_begin_step,
             pnn,
             {
                 &C_icon_eye,
                 "Review",
                 g_welcome,
             });

UX_FLOW(ux_dynamic_display_flow,
        &ux_display_review_begin_step,  // static ux

        &step_upper_delimiter,  // A special step that serves as the upper delimiter. It won't print
                                // anything on the screen.
        &step_generic,          // The generic step that will actually display stuff on the screen.
        &step_lower_delimiter,  // A special step that serves as the lower delimiter. It won't print
                                // anything on the screen.

        &ux_display_approve_step,
        &ux_display_reject_step,
        FLOW_LOOP);

int ui_display_address() {
    if (G_context.req_type != CONFIRM_ADDRESS || G_context.state != STATE_NONE) {
        G_context.state = STATE_NONE;
        return io_send_sw(SW_BAD_STATE);
    }

    global.max = 4;
    // do a dry run to check for errors
    for (int i = 0; i < global.max; ++i) {
        int e = dynamic_display_address(i);
        if (e < 0) {
            return e;
        }
    }

    global.dynamic_flow = dynamic_display_address;
    snprintf(g_welcome, sizeof(g_welcome), "Key Information");
    g_validate_callback = &ui_action_validate_pubkey;
    ux_flow_init(0, ux_dynamic_display_flow, NULL);

    return 0;
}

int ui_display_transaction(void) {
    PRINTF("checkpoint pre display tx 1\n");

    if (G_context.req_type != CONFIRM_TRANSACTION || G_context.state != STATE_PARSED) {
        G_context.state = STATE_NONE;
        return io_send_sw(SW_BAD_STATE);
    }

    g_HaveMemoField = 0;

    explicit_bzero(&global, sizeof(global));
    global.current_state = STATIC_SCREEN;
    if (G_context.tx_info.transaction->Header.Memo.data.buffer.ptr &&
        (G_context.tx_info.transaction->Header.Memo.data.buffer.size -
         G_context.tx_info.transaction->Header.Memo.data.buffer.offset)) {
        g_HaveMemoField = 1;
    }
    switch ((int) G_context.tx_info.transaction->Body._u->Type) {
        case TransactionTypeAddCredits: {
            PRINTF("AddCredits tx\n");

            global.max = 3 + g_HaveMemoField;
            // do a dry run to check for errors
            for (int i = 0; i < global.max; ++i) {
                int e = ui_dynamic_display_add_credits(i);
                if (e < 0) {
                    PRINTF("An error occured in the AddCredits display at step %d, err %d\n", i, e);
                    return e;
                }
            }

            snprintf(g_welcome, sizeof(g_welcome), "Add Credits");
            g_validate_callback = &ui_action_validate_transaction_hash;
            global.dynamic_flow = ui_dynamic_display_add_credits;
            ux_flow_init(0, ux_dynamic_display_flow, NULL);
            break;
        }
        case TransactionTypeSendTokens: {
            // set up the global dynamic display for send tokens
            SendTokens *s = G_context.tx_info.transaction->Body._SendTokens;
            if (s->To_length == 0) {
                PRINTF("SendTokens tx amount failing\n");
                return SW_DISPLAY_AMOUNT_FAIL;
            }

            global.max = 1 + g_HaveMemoField;
            global.max += 2 * s->To_length;

            // do a dry run to check for errors
            for (int i = 0; i < global.max; ++i) {
                int e = ui_dynamic_display_send_tokens(i);
                if (e < 0) {
                    return e;
                }
            }

            global.dynamic_flow = ui_dynamic_display_send_tokens;
            snprintf(g_welcome, sizeof(g_welcome), "Send Tokens");
            g_validate_callback = &ui_action_validate_transaction_hash;
            ux_flow_init(0, ux_dynamic_display_flow, NULL);
            break;
        }
        default:
            return ErrorTypeNotFound;
    }

    return 0;
}
