#include "dynamic_display.h"

#include <stdbool.h>
#include <types.h>

#include "../glyphs.h"
#include "os.h"
#include "ux.h"

#ifndef UNUSED
#define UNUSED(X) (void) (X);
#endif

DynamicDisplay global;
extern ux_state_t G_ux;
extern bolos_ux_params_t G_ux_params;

void display_next_state(bool is_upper_delimiter);
// Note we're using UX_STEP_INIT because this step won't display anything.
UX_STEP_INIT(step_upper_delimiter, NULL, NULL, {
    // This function will be detailed later on.
    display_next_state(true);
});

UX_STEP_NOCB(step_generic,
             bnnn_paging,
             {
                 .title = global.title,
                 .text = global.text,
             });

// Note we're using UX_STEP_INIT because this step won't display anything.
UX_STEP_INIT(step_lower_delimiter, NULL, NULL, {
    // This function will be detailed later on.
    display_next_state(false);
});

UX_STEP_NOCB(step_welcome,
             pnn,
             {
                 &C_icon_eye,
                 "Welcome",
                 "Do Something",
             });

UX_STEP_NOCB(step_quit,
             pnn,
             {
                 &C_icon_eye,
                 "Good Bye",
                 "Don't do anything",
             });

UX_FLOW(dynamic_test_flow,
        &step_welcome,

        &step_upper_delimiter,  // A special step that serves as the upper delimiter. It won't print
                                // anything on the screen.
        &step_generic,          // The generic step that will actually display stuff on the screen.
        &step_lower_delimiter,  // A special step that serves as the lower delimiter. It won't print
                                // anything on the screen.

        &step_quit,
        FLOW_LOOP);

// This is a special function you must call for bnnn_paging to work properly in an edgecase.
// It does some weird stuff with the `G_ux` global which is defined by the SDK.
// No need to dig deeper into the code, a simple copy-paste will do.
void bnnn_paging_edgecase() {
    G_ux.flow_stack[G_ux.stack_count - 1].prev_index =
        G_ux.flow_stack[G_ux.stack_count - 1].index - 2;
    G_ux.flow_stack[G_ux.stack_count - 1].index--;
    ux_flow_relayout();
}

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
            ux_flow_next();
        } else {
            // The previous screen was NOT a static screen, so we were already in a dynamic screen.

            // Fetch new data.
            bool dynamic_data = get_next_data(global.title, global.text, is_upper_delimiter, false);
            if (dynamic_data) {
                // We found some data so simply display it.
                ux_flow_next();
            } else {
                // There's no more dynamic data to display, so
                // update the current state accordingly.
                global.current_state = STATIC_SCREEN;

                // Display the previous screen which should be a static one.
                ux_flow_prev();
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
            ux_flow_prev();
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
                ux_flow_next();
            }
        }
    }
}

void debug_display() {
    explicit_bzero(&global, sizeof(global));
    global.dynamic_flow = step_test;
    global.max = 10;
    ux_flow_init(0, dynamic_test_flow, NULL);
}
