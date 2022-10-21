
#include "display_transaction.h"

int ui_dynamic_display_add_credits(int index) {
    AddCredits *ac = G_context.tx_info.transaction.Body._AddCredits;
    switch(index) {
        case 0:
            return display_transaction_principal();
        case 1: {
            snprintf(global.title,sizeof(global.title), "Recipient URL");
            Error e = Url_get(&ac->Recipient, global.text, sizeof(global.text));
            if (IsError(e)) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text),"code %d", e.code);
                return e.code;
            }
        } break;
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
        } break;
        default:
            return display_memo_or_error();
    }
    return ErrorNone;
}
