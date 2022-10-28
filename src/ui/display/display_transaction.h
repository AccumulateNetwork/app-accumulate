#pragma once

#include "ux.h"
#include <common/error.h>
#include <encoding/string.h>
#include "types.h"
#include "ui/dynamic_display.h"
#include "globals.h"
#include "address.h"

int display_transaction_principal(void);
int display_memo_or_error(void);

int ui_dynamic_display_add_credits(int index);
int ui_dynamic_display_send_tokens(int index);

extern int g_HaveMemoField;



