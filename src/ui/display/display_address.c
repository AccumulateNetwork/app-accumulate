
#include "display.h"
#include "ui/action/validate.h"
#include "ui/dynamic_display.h"
#include "../../address.h"

// Step with icon and text
UX_STEP_NOCB(ux_display_confirm_addr_step, pn, {&C_icon_eye, "Confirm Key Name"});

int dynamic_display_address(int index) {
    switch(index) {
        case 0:
            snprintf(global.title,sizeof(global.title), "Key Path");
            explicit_bzero(global.text, sizeof(global.text));
            if (!bip32_path_format(G_context.bip32_path,
                                   G_context.bip32_path_len,
                                   global.text,
                                   sizeof(global.text))) {
                return SW_DISPLAY_BIP32_PATH_FAIL;
            }
            break;
        case 1:
            snprintf(global.title,sizeof(global.title), "Key Name");
            snprintf(global.text,sizeof(global.text),"%s", G_context.pk_info.address_name);
            break;
        case 2:
            explicit_bzero(global.text,sizeof(global.text));
            snprintf(global.title, sizeof(global.title), "Multi-Hash");
            encodeMultihash(G_context.pk_info.hash,sizeof(G_context.pk_info.hash), global.text, sizeof(global.text));
        case 3:
            snprintf(global.title, sizeof(global.title), "Lite Identity");
            snprintf(global.text, sizeof(global.text), "%s", G_context.pk_info.lite_account);
            break;
        default:
            //defensive message, should never get here
            snprintf(global.title, sizeof(global.title), "error");
            snprintf(global.text, sizeof(global.text), "unknown %d", index);
            return ErrorTypeNotFound;
    }
    return ErrorNone;
}
