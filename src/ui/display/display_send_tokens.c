
#include "display_transaction.h"
#include <protocol/transaction.h>

int ui_dynamic_display_send_tokens(int index) {
    PRINTF("Dynamic Display %d\n", index);
    if (index == 0) {
        // display principal
        return display_transaction_principal();
    }
    if (index == global.max - 1 && g_HaveMemoField) {
        return display_memo_or_error();
    } else {
        // loop through transactions and display those.
        const int offset = 1;
        if (((index - offset) % 2) == 0) {
            // display the destination URL
            int localIndex = (index - offset) / 2;
            Error e = Url_get(&G_context.tx_info.transaction.Body._SendTokens->To[localIndex].Url,
                              global.text,
                              sizeof(global.text));
            if (IsError(e)) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text), "code %d", e.code);
                return e.code;
            }
            snprintf(global.title, sizeof(global.title), "Output %d URL", localIndex + 1);
        } else {
            // display the destination amount
            int localIndex = (index - offset - 1) / 2;
            snprintf(global.title, sizeof(global.title), "Output %d Amount", localIndex + 1);
            if (localIndex > (int) G_context.tx_info.transaction.Body._SendTokens->To_length) {
                snprintf(global.title, sizeof(global.title), "Send To error");
                snprintf(global.text,
                         sizeof(global.text),
                         "out of bounds %d>%d",
                         localIndex,
                         G_context.tx_info.transaction.Body._SendTokens->To_length);
                return ErrorInvalidData;
            }
            uint256_t i;
            BigInt *amount = &G_context.tx_info.transaction.Body._SendTokens->To[localIndex].Amount;
            int e = frombytes256(amount->data.buffer.ptr + amount->data.buffer.offset,
                                 amount->data.buffer.size - amount->data.buffer.offset,
                                 &i);
            if (e < 0) {
                return ErrorInvalidBigInt;
            }
            {
                char amountString[32] = {0};
                if (!tostring256(&i, 10, amountString, sizeof(amountString))) {
                    return ErrorInvalidBigInt;
                }
                // note: this will only work with acme send tokens right now,
                //  if a token exists that doesn't have a precision of 8, this will not display
                //  correctly
                if (!adjustDecimals(amountString,
                                    strlen(amountString),
                                    global.text,
                                    sizeof(global.text),
                                    ACME_PRECISION)) {
                    return ErrorInvalidString;
                }
            }
        }
    }
    return 0;
}
