
#include "display_transaction.h"
#include <protocol/unions.h>
#include <common/format.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

int ui_dynamic_display_blind_signing(int index) {
    SignatureTypeUnion *signer = G_context.tx_info.signer->_u;
    switch (index) {
        case 0:
            PRINTF("Blind signing display %d\n", index);
            snprintf(global.title, sizeof(global.title), "Blind Signing");
            snprintf(global.text, sizeof(global.text), "Request");
            break;
        case 1: {
            PRINTF("Blind Sign %d\n", index);
            snprintf(global.title, sizeof(global.title), "Signer URL");
            Error e = Url_get(&signer->Signer, global.text, sizeof(global.text));
            if (IsError(e)) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text), "code %d", e.code);
                return e.code;
            }
        } break;
        case 2: {
            PRINTF("Blind Sign %d\n", index);
            snprintf(global.title, sizeof(global.title), "Signer Version");
            uint64_t version = 0;
            Error e = UVarInt_get(&signer->SignerVersion, &version);
            if (IsError(e)) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text), "code %d", e.code);
                return e.code;
            }
            snprintf(global.text, sizeof(global.text), "%"PRIu64"", version);
        } break;
        case 3: {
            PRINTF("Blind Sign %d\n", index);
            snprintf(global.title, sizeof(global.title), "Timestamp/Nonce");
            uint64_t timestamp = 0;
            Error e = UVarInt_get(&signer->Timestamp, &timestamp);
            if (IsError(e)) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text), "code %d", e.code);
                return e.code;
            }
            snprintf(global.text, sizeof(global.text), "%"PRIu64"", timestamp);
        } break;
        case 4: {
            PRINTF("Blind Sign %d\n", index);
            snprintf(global.title, sizeof(global.title), "Transaction Hash");
            int bytesWritten = format_hex(signer->TransactionHash.data.buffer.ptr + signer->TransactionHash.data.buffer.offset, 
                                          signer->TransactionHash.data.buffer.size, global.text, sizeof(global.text));
            if (bytesWritten != 32) {
                snprintf(global.title, sizeof(global.title), "error");
                snprintf(global.text, sizeof(global.text), "print hash %d", bytesWritten);
                return ErrorBadCopy;
            }
        } break;
        default:
            PRINTF("Blind Sign %d\n", index);
            snprintf(global.title, sizeof(global.title), "Invalid");
            snprintf(global.text, sizeof(global.text), "Display State");
            return ErrorInvalidField;
    }
    return ErrorNone;
}
