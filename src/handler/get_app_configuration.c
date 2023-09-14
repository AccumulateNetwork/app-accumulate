
#include "get_app_configuration.h"

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
    return helper_send_response_app_configuration();
}
