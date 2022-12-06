
#include "display_transaction.h"

int ui_dynamic_display_add_credits(int index) {
    AddCredits *ac = G_context.tx_info.transaction->Body._AddCredits;
    switch (index) {
        case 0:
            PRINTF("AddCredits display %d\n", index);
            return display_transaction_principal();
        case 1: {
            PRINTF("AddCredits display %d\n", index);
            snprintf(global.title, sizeof(global.title), "Recipient URL");
            Error e = Url_get(&ac->Recipient, global.text, sizeof(global.text));
            if (IsError(e)) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text), "code %d", e.code);
                return e.code;
            }
        } break;
        case 2: {
            snprintf(global.title, sizeof(global.title), "Credits");

            uint256_t amountToSpend;
            explicit_bzero(&amountToSpend, sizeof(amountToSpend));
            Error e = BigInt_get(&ac->Amount, &amountToSpend);
            if (IsError(e)) {
                return ErrorInvalidBigInt;
            }

            // compute the oracle conversion
            uint256_t oracle;
            explicit_bzero(&oracle, sizeof(oracle));
            UVarInt_get(&ac->Oracle,&oracle.elements[1].elements[1]);
            oracle.elements[1].elements[1] *= CREDITS_PER_FIAT_UNIT;

            // compute amount of credits from ACME spend sans precision
            uint256_t credits;
            explicit_bzero(&credits, sizeof(credits));
            mul256(&oracle, &amountToSpend, &credits);

            char amountString[128] = {0};
            if (!tostring256(&credits, 10, amountString, sizeof(amountString))) {
                return ErrorInvalidBigInt;
            }

            if (!adjustDecimals(amountString,
                                strlen(amountString),
                                global.text,
                                sizeof(global.text),
                                CREDITS_PRECISION+ACME_PRECISION+ORACLE_PRECISION)) {
                return ErrorInvalidString;
            }
        } break;
        default:
            PRINTF("AddCredits display %d\n", index);
            return display_memo_or_error();
    }
    return ErrorNone;
}
