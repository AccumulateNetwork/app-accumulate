
#include "get_blind_signing_token.h"

#include <common/buffer.h>
#include <common/error.h>
#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdint.h>   // uint*_t
#include <string.h>   // memset, explicit_bzero

#include "../globals.h"
#include "../helper/send_response.h"
#include "../io.h"
#include "../sw.h"
#include "../types.h"
#include "../ui/display/display.h"

int handler_get_app_configuration() {
    // explicit_bzero(&G_context, sizeof(G_context));
    // explicit_bzero(&G_settings_context.blind_signing_enabled);

    return helper_send_response_blind_signing_token();
}
