
#include "display_transaction.h"
#include "display.h"
#include "ui/dynamic_display.h"


int display_transaction_principal(void) {
    if (G_context.req_type != CONFIRM_TRANSACTION || G_context.state != STATE_PARSED) {
        G_context.state = STATE_NONE;
        snprintf(global.title,sizeof(global.title), "error");
        snprintf(global.text, sizeof(global.text), "bad tx state");
        return io_send_sw(SW_BAD_STATE);
    }
    //display principal
    Error e = Url_get(&G_context.tx_info.transaction.Header.Principal, global.text, sizeof(global.text));
    if (IsError(e)) {
        snprintf(global.title, sizeof(global.title), "error");
        snprintf(global.text, sizeof(global.text), "code %d", e.code);
        return e.code;
    }
    snprintf(global.title,sizeof(global.title), "Principal URL");
    return ErrorNone;
}
