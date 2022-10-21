
#include "ui/display/display_transaction.h"

int display_memo_or_error(void) {
    if ( g_HaveMemoField ) {
        snprintf(global.title, sizeof(global.title), "Memo");
        Error e = String_get(&G_context.tx_info.transaction.Header.Memo, global.text, sizeof(global.text));
    } else {
        snprintf(global.title, sizeof(global.title), "Invalid");
        snprintf(global.text, sizeof(global.text), "Display State");
        return ErrorInvalidField;
    }

    return ErrorNone;
}
