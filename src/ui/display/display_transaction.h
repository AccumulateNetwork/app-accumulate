#pragma once

#include "common/error.h"
#include "ux.h"
#include "string.h"
#include "types.h"
#include "ui/dynamic_display.h"
#include "globals.h"
#include "address.h"

int display_transaction_principal();

int ui_dynamic_display_add_credits(int index);
int ui_dynamic_display_send_tokens(int index);

