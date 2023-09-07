
#include "get_blind_signing_token.h"

#include <common/buffer.h>
#include <common/error.h>
#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdint.h>   // uint*_t
#include <string.h>   // memset, explicit_bzero

#include "../helper/send_response.h"
#include "../io.h"
#include "../sw.h"
#include "../types.h"
#include "../ui/display/display.h"

int handler_get_blind_signing_token() {
    explicit_bzero(&G_Context);
    explicit_bzero(&G_blind_context, sizeof(G_blind_context));
    return ui_display_blind_signing_enable();
}

int handler_clear_blind_signing_token() {
    explicit_bzero(&G_Context);
    explicit_bzero(&G_blind_context, sizeof(G_blind_context));
    return io_send_sw(SW_OK);
}
