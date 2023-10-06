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

#include "display.h"

action_validate_cb g_validate_callback;
char g_welcome[32];
int g_HaveMemoField;

int ui_display_blind_signing_requested() {
    if (G_context.req_type != CONFIRM_TRANSACTION || G_context.state != STATE_PARSED) {
        G_context.state = STATE_NONE;
        return io_send_sw(SW_BAD_STATE);
    }

    g_HaveMemoField = 0;
    explicit_bzero(&global, sizeof(global));
    global.max = 5;
    // dry run the menu options to catch any errors
    for (int i = 0; i < global.max; ++i) {
        int e = ui_dynamic_display_blind_signing(i);
        if (e < 0) {
            PRINTF("An error occurred in the Blind siging display at step %d, err %d\n", i, e);
            return e;
        }
    }
    snprintf(g_welcome, sizeof(g_welcome), "Blind Signing");
    g_validate_callback = &ui_action_validate_transaction;
    global.dynamic_flow = ui_dynamic_display_blind_signing;
    ux_flow_init(0, ux_dynamic_display_flow, NULL);

    return 0;
}
