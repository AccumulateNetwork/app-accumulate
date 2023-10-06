#pragma once

#include <common/error.h>
#include <encoding/string.h>

#include "address.h"
#include "globals.h"
#include "types.h"
#include "ui/dynamic_display.h"
//#include "ux.h"

int display_transaction_principal(void);
int display_memo_or_error(void);

int ui_dynamic_display_add_credits(int index);
int ui_dynamic_display_send_tokens(int index);
int ui_dynamic_display_blind_signing(int index);

extern int g_HaveMemoField;
