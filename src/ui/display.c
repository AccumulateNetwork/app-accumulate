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

#include <stdbool.h>  // bool
#include <string.h>   // memset

#include "os.h"
#include "ux.h"
#include "../glyphs.h"

#include "display.h"
#include "../constants.h"
#include "../globals.h"
#include "../io.h"
#include "../sw.h"
#include "../address.h"
#include "action/validate.h"
#include "../transaction/types.h"
#include "../common/bip32.h"
#include "../common/format.h"
#include "dynamic_display.h"
#include "globals.h"

static action_validate_cb g_validate_callback;
//static char g_amount[30];
static char g_bip32_path[60];
static char g_welcome[32];
static char g_address[MAX_ACME_LITE_ACCOUNT_LEN];
//static char g_address_name[64];
//static char g_lite_account[MAX_ACME_LITE_ACCOUNT_LEN];


#define min(a,b) (a<b?a:b)

// display stepped screens
unsigned int ux_step;
unsigned int ux_step_count;


// Step with icon and text
UX_STEP_NOCB(ux_display_confirm_addr_step, pn, {&C_icon_eye, "Confirm Key Name"});
// Step with title/text for BIP32 path
UX_STEP_NOCB(ux_display_path_step,
             bnnn_paging,
             {
                 .title = "Path",
                 .text = g_bip32_path,
             });
// Step with title/text for address
UX_STEP_NOCB(ux_display_address_step,
             bnnn_paging,
             {
                 .title = "Key Name",
                 .text =  g_address,
             });
// Step with title/text for address
UX_STEP_NOCB(ux_display_lite_step,
             bnnn_paging,
             {
                 .title = "Lite Identity",
                 .text =  G_context.pk_info.lite_account,
             });

UX_STEP_NOCB(ux_display_signer_url,
             bnnn_paging,
             {
                 .title = "Lite Identity",
                 .text =  G_context.pk_info.lite_account,
             });

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

// FLOW to display address and BIP32 path:
// #1 screen: eye icon + "Confirm Address"
// #2 screen: display BIP32 Path
// #3 screen: display address
// #4 screen: approve button
// #5 screen: reject button
UX_FLOW(ux_display_pubkey_flow,
        &ux_display_confirm_addr_step,
        &ux_display_path_step,
        &ux_display_address_step,
        &ux_display_lite_step,
        &ux_display_approve_step,
        &ux_display_reject_step);

int ui_display_address() {
    if (G_context.req_type != CONFIRM_ADDRESS || G_context.state != STATE_NONE) {
        G_context.state = STATE_NONE;
        return io_send_sw(SW_BAD_STATE);
    }

    memset(g_bip32_path, 0, sizeof(g_bip32_path));
    if (!bip32_path_format(G_context.bip32_path,
                           G_context.bip32_path_len,
                           g_bip32_path,
                           sizeof(g_bip32_path))) {
        return io_send_sw(SW_DISPLAY_BIP32_PATH_FAIL);
    }

    strncpy(g_address, G_context.pk_info.address_name, sizeof (G_context.pk_info.address_name));
    g_validate_callback = &ui_action_validate_pubkey;

    ux_flow_init(0, ux_display_pubkey_flow, NULL);

    return 0;
}


// Step with icon and text
UX_STEP_NOCB(ux_display_review_begin_step,
             pnn,
             {
                 &C_icon_eye,
                 "Review",
                 g_welcome,
             });

UX_FLOW(ux_dynamic_display_flow,
        &ux_display_review_begin_step, //static ux

        &step_upper_delimiter, // A special step that serves as the upper delimiter. It won't print anything on the screen.
        &step_generic, // The generic step that will actually display stuff on the screen.
        &step_lower_delimiter, // A special step that serves as the lower delimiter. It won't print anything on the screen.

        &ux_display_approve_step,
        &ux_display_reject_step,
        FLOW_LOOP
);


int display_principal() {
    //display principal
    Error e = Url_get(&G_transaction.Header.Principal, global.text, sizeof(global.text));
    if (IsError(e)) {
        strcpy(global.title, "error");
        strcpy(global.text, e.err);
        return e.code;
    }
    strcpy(global.title, "Principal URL");
    return ErrorNone;
}

int ui_dynamic_display_add_credits(int index) {
    AddCredits *ac = G_transaction.Body._AddCredits;
    switch(index) {
        case 0:
            return display_principal();
        case 1: {
            snprintf(global.title,sizeof(global.title), "Recipient URL");
            Error e = Url_get(&ac->Recipient, global.text, sizeof(global.text));
            if (IsError(e)) {
                strcpy(global.title, "error");
                strcpy(global.text, e.err);
                return e.code;
            }
        }
        break;
        case 2: {
            uint256_t i;
            snprintf(global.title,sizeof(global.title), "Credits");
            BigInt *amount = &ac->Amount;
            int e = frombytes256(amount->data.buffer.ptr+amount->data.buffer.offset,
                                 amount->data.buffer.size - amount->data.buffer.offset,&i);
            if ( e < 0 ) {
                return ErrorInvalidBigInt;
            }
            char amountString[32] = {0};
            if (!tostring256(&i, 10, amountString, sizeof(amountString))) {
                return ErrorInvalidBigInt;
            }
            if ( !adjustDecimals(amountString,strlen(amountString),global.text,sizeof(global.text), CREDITS_PRECISION) ) {
                return ErrorInvalidString;
            }
        }
        break;
        default: {
            strcpy(global.title, "Invalid");
            strcpy(global.text, "Display State");
            return ErrorInvalidField;
        }
    }
    return 0;
}
int ui_dynamic_display_send_tokens(int index) {
    PRINTF("Dynamic Display %d\n", index);
    if ( index == 0 ) {
        //display principal
        return display_principal();
    } else {
        //loop through transactions and display those.
        const int offset = 1;
        if ( ((index-offset) % 2) == 0) {
            //display the destination URL
            int localIndex = (index-offset)/2;
            Error e = Url_get(&G_transaction.Body._SendTokens->To[localIndex].Url,
                              global.text, sizeof(global.text));
            if (IsError(e)) {
                strcpy(global.title, "error");
                strcpy(global.text, e.err);
                return e.code;
            }
            snprintf(global.title,sizeof(global.title), "Output %d URL", localIndex+1);
            SendTokens *s = G_transaction.Body._SendTokens;
            PRINTF("URL : %.*s" , s->To[localIndex].Url.data.buffer.size - s->To[localIndex].Url.data.buffer.offset,
                   s->To[localIndex].Url.data.buffer.ptr+s->To[localIndex].Url.data.buffer.offset);

        } else {
            //display the destination amount
            int localIndex = (index-offset-1)/2;
            snprintf(global.title,sizeof(global.title), "Output %d Amount", localIndex+1);
            if ( localIndex > (int)G_transaction.Body._SendTokens->To_length) {
                strcpy(global.title, "Send To error");
                snprintf(global.text,sizeof (global.text),"out of bounds %d>%d",localIndex,
                         G_transaction.Body._SendTokens->To_length);
                return ErrorInvalidData;
            }
            uint256_t i;
            BigInt *amount = &G_transaction.Body._SendTokens->To[localIndex].Amount;
            int e = frombytes256(amount->data.buffer.ptr+amount->data.buffer.offset,
                         amount->data.buffer.size - amount->data.buffer.offset,&i);
            if ( e < 0 ) {
                return ErrorInvalidBigInt;
            }
            {
                char amountString[32] = {0};
                if (!tostring256(&i, 10, amountString, sizeof(amountString))) {
                    return ErrorInvalidBigInt;
                }
                //note: this will only work with acme send tokens right now,
                // if a token exists that doesn't have a precision of 8, this will not display correctly
                if ( !adjustDecimals(amountString,strlen(amountString),global.text,sizeof(global.text), ACME_PRECISION) ) {
                    return ErrorInvalidString;
                }
            }
        }
    }
    return 0;
}

int ui_display_transaction(Signature *signer, Transaction *transaction) {
    PRINTF("checkpoint pre display tx 1\n");

    if (G_context.req_type != CONFIRM_TRANSACTION || G_context.state != STATE_PARSED) {
        G_context.state = STATE_NONE;
        return io_send_sw(SW_BAD_STATE);
    }

    explicit_bzero(&global, sizeof(global));
    global.current_state = STATIC_SCREEN;
    PRINTF("Address of Body: %p\n", ( void * )transaction->Body._u );
    switch ((int)transaction->Body._u->Type) {
        case TransactionTypeAddCredits: {
            PRINTF("AddCredits tx\n");

            global.max = 3;
            //do a dry run to check for errors
            for ( int i = 0; i < global.max; ++i) {
                int e = ui_dynamic_display_add_credits(i);
                if ( e < 0 ) {
                    return e;
                }
            }

            strncpy(g_welcome, "Add Credits", sizeof(g_welcome));
            g_validate_callback = &ui_action_validate_transaction_hash;
            global.dynamic_flow = ui_dynamic_display_add_credits;
            ux_flow_init(0, ux_dynamic_display_flow, NULL);
            break;
        }
        case TransactionTypeSendTokens: {
            //set up the global dynamic display for send tokens
            SendTokens *s = transaction->Body._SendTokens;
            if ( s->To_length == 0 ) {
                PRINTF("SendTokens tx amount failing\n");
                return SW_DISPLAY_AMOUNT_FAIL;
            }

            global.max = 1;
            global.max += 2*s->To_length;

            //do a dry run to check for errors
            for ( int i = 0; i < global.max; ++i) {
                int e = ui_dynamic_display_send_tokens(i);
                if ( e < 0 ) {
                    return e;
                }
            }

            global.dynamic_flow = ui_dynamic_display_send_tokens;
            strncpy(g_welcome, "Send Tokens", sizeof(g_welcome));
            g_validate_callback = &ui_action_validate_transaction_hash;
            ux_flow_init(0, ux_dynamic_display_flow, NULL);
            break;
        }
        default:
            return ErrorTypeNotFound;
    }

    return 0;
}
