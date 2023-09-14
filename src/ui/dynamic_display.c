#include "dynamic_display.h"

#include <stdbool.h>
#include <types.h>

#include "glyphs.h"
#include "os.h"
#include "ux.h"

#ifndef UNUSED
#define UNUSED(X) (void) (X);
#endif

DynamicDisplay global;

void display_next_state(bool is_upper_delimiter);

int step_test(int index) {
    snprintf(global.title, sizeof(global.title), "step_test");
    snprintf(global.text, sizeof(global.text), "<%d | >", index);
    return 0;
}

bool get_next_data(char *title, char *text, bool is_upper_delimiter, bool next) {
    UNUSED(title);
    UNUSED(text);
    UNUSED(is_upper_delimiter);

    // adjust the step to current offset....
    global.index = (next) ? ++global.index : --global.index;
    if (global.index >= global.max) {
        return false;
    } else if (global.index < 0) {
        return false;
    }

    if (global.dynamic_flow) {
        global.dynamic_flow(global.index);
    }

    return true;
}

// Main function that handles all the business logic for our new display architecture.
void display_next_state(bool is_upper_delimiter) {
    if (is_upper_delimiter) {  // We're called from the upper delimiter.
        if (global.current_state == STATIC_SCREEN) {
            // Fetch new data.

            global.index = -1;
            bool dynamic_data = get_next_data(global.title, global.text, is_upper_delimiter, true);

            if (dynamic_data) {
                // We found some data to display so we now enter in dynamic mode.
                global.current_state = DYNAMIC_SCREEN;
            }

            // Move to the next step, which will display the screen.
            flow_next();
        } else {
            // The previous screen was NOT a static screen, so we were already in a dynamic screen.

            // Fetch new data.
            bool dynamic_data = get_next_data(global.title, global.text, is_upper_delimiter, false);
            if (dynamic_data) {
                // We found some data so simply display it.
                flow_next();
            } else {
                // There's no more dynamic data to display, so
                // update the current state accordingly.
                global.current_state = STATIC_SCREEN;

                // Display the previous screen which should be a static one.
                flow_prev();
            }
        }
    } else {
        // We're called from the lower delimiter.

        if (global.current_state == STATIC_SCREEN) {
            global.index = global.max;
            // Fetch new data.
            bool dynamic_data = get_next_data(global.title, global.text, is_upper_delimiter, false);

            if (dynamic_data) {
                // We found some data to display so enter in dynamic mode.
                global.current_state = DYNAMIC_SCREEN;
            }

            // Display the data.
            flow_prev();
        } else {
            // We're being called from a dynamic screen, so the user was already browsing the array.

            // Fetch new data.
            bool dynamic_data = get_next_data(global.title, global.text, is_upper_delimiter, true);
            if (dynamic_data) {
                // We found some data, so display it.
                // Similar to `ux_flow_prev()` but updates layout to account for `bnnn_paging`'s
                // weird behaviour.
                bnnn_paging_edgecase();
            } else {
                // We found no data so make sure we update the state accordingly.
                global.current_state = STATIC_SCREEN;

                // Display the next screen
                flow_next();
            }
        }
    }
}
