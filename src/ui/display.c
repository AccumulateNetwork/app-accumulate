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

static action_validate_cb g_validate_callback;
static char g_amount[30];
static char g_bip32_path[60];
static char g_address[MAX_ACME_LITE_ACCOUNT_LEN];
//static char g_address_name[64];
//static char g_lite_account[MAX_ACME_LITE_ACCOUNT_LEN];


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
UX_STEP_NOCB(ux_display_review_send_tokens_step,
             pnn,
             {
                 &C_icon_eye,
                 "Review",
                 "Send Tokens",
             });

UX_STEP_NOCB(ux_display_review_add_credits_step,
             pnn,
             {
                 &C_icon_eye,
                 "Review",
                 "Add Credits",
             });
// Step with title/text for amount
UX_STEP_NOCB(ux_display_amount_step,
             bnnn_paging,
             {
                 .title = "Amount",
                 .text = g_amount,
             });

UX_STEP_NOCB(ux_display_hash_step,
             bnnn_paging,
             {
                 .title = "Transaction Hash",
                 .text = g_address,
             });




UX_FLOW(ux_display_transaction_hash_flow,
        &ux_display_hash_step,
        &ux_display_approve_step,
        &ux_display_reject_step);

// FLOW to display transaction information:
// #1 screen : eye icon + "Review Transaction"
// #2 screen : display amount
// #3 screen : display destination address
// #4 screen : approve button
// #5 screen : reject button
UX_FLOW(ux_display_send_tokens_flow,
        &ux_display_review_send_tokens_step,
        &ux_display_address_step,
        &ux_display_amount_step,
        &ux_display_approve_step,
        &ux_display_reject_step);

// FLOW to display transaction information:
// #1 screen : eye icon + "Review Transaction"
// #2 screen : display amount
// #3 screen : display destination address
// #4 screen : approve button
// #5 screen : reject button
UX_FLOW(ux_display_add_credits_flow,
        &ux_display_review_add_credits_step,
        &ux_display_address_step,
        &ux_display_amount_step,
        &ux_display_approve_step,
        &ux_display_reject_step);

int setDisplayAmount(Url *url, BigInt *amount) {
    CHECK_ERROR_INT(url)
    CHECK_ERROR_INT(amount)

    uint256_t i;
    frombytes256(amount->data.buffer.ptr+amount->data.buffer.offset,
                 amount->data.buffer.size - amount->data.buffer.offset,&i);
    if ( !tostring256(&i, 10, g_amount,sizeof (g_amount))) {
        return ErrorInvalidBigInt;
    }
    explicit_bzero(g_address, sizeof(g_address));
    Error e = Url_get(url,g_address, sizeof (g_address)-1);
    if (IsError(e)) {
        return e.code;
    }
}

int ui_display_transaction(Signature *signer, Transaction *transaction) {

    PRINTF("checkpoint pre display tx 1\n");

    if (G_context.req_type != CONFIRM_TRANSACTION || G_context.state != STATE_PARSED) {
        G_context.state = STATE_NONE;
        return io_send_sw(SW_BAD_STATE);
    }
//    format_hex(G_context.tx_info.m_hash, sizeof(G_context.tx_info.m_hash), g_address, sizeof(g_address));
//    PRINTF("checkpoint pre display tx 2 %s\n", g_address);
//
//    memset(g_address, 0, sizeof(g_address));
//    snprintf(g_address, sizeof(g_address), "0x%.*H", 32, G_context.tx_info.m_hash);
//    g_validate_callback = &ui_action_validate_transaction_hash;
//    ux_flow_init(0, ux_display_transaction_hash_flow, NULL);

//    return 0;
    //decode the signer
    //signerBuffer
    //decode transaction type:
    PRINTF("Address of Body: %p\n", ( void * )transaction->Body._u );
    switch ((int)transaction->Body._u->Type) {
        case TransactionTypeAddCredits: {

            PRINTF("AddCredits tx\n");
            AddCredits *c = transaction->Body._AddCredits;
            int e = setDisplayAmount(&c->Recipient, &c->Amount);
            if (IsError(ErrorCode(e))) {
                return e;
            }
            g_validate_callback = &ui_action_validate_transaction_hash;
            ux_flow_init(0, ux_display_add_credits_flow, NULL);
            break;
        }
        case TransactionTypeSendTokens: {

                       PRINTF("SendTokens tx\n");
            SendTokens *s = transaction->Body._SendTokens;
            if ( s->To_length > 1 || s->To_length == 0 ) {

                PRINTF("SendTokens tx amount failing\n");
                return SW_DISPLAY_AMOUNT_FAIL;
            }

            PRINTF("URL : %.*s" , s->To[0].Url.data.buffer.size - s->To[0].Url.data.buffer.offset,
                   s->To[0].Url.data.buffer.ptr+s->To[0].Url.data.buffer.offset);
            int e = setDisplayAmount(&s->To[0].Url, &s->To[0].Amount);
            if (IsError(ErrorCode(e))) {

                PRINTF("SendTokens tx set Display Amount failed\n");
                return e;
            }

            snprintf(g_address,sizeof (g_address), "%.*s", s->To[0].Url.data.buffer.size - s->To[0].Url.data.buffer.offset,
                     s->To[0].Url.data.buffer.ptr+s->To[0].Url.data.buffer.offset);
            g_validate_callback = &ui_action_validate_transaction_hash;
            ux_flow_init(0, ux_display_send_tokens_flow, NULL);
            break;
        }
        default:
            return ErrorTypeNotFound;
    };


//
//    memset(g_amount, 0, sizeof(g_amount));
//    char amount[30] = {0};
//    if (!format_fpu64(amount,
//                      sizeof(amount),
//                      G_context.tx_info.transaction.value,
//                      EXPONENT_SMALLEST_UNIT)) {
//        return io_send_sw(SW_DISPLAY_AMOUNT_FAIL);
//    }
//    snprintf(g_amount, sizeof(g_amount), "BOL %.*s", sizeof(amount), amount);
//    PRINTF("Amount: %s\n", g_amount);

//    memset(g_address, 0, sizeof(g_address));
//    snprintf(g_address, sizeof(g_address), "0x%.*H", ADDRESS_LEN, G_context.tx_info.transaction.to);

    //g_validate_callback = &ui_action_validate_transaction_hash;

    //ux_flow_init(0, ux_display_transaction_flow, NULL);

    return 0;
}
