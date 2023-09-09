#include <stdbool.h>
#include <types.h>

#include "dynamic_display.h"
#include "glyphs.h"
#include "os.h"
#include "ux.h"

#ifndef UNUSED
#define UNUSED(X) (void) (X);
#endif

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

void flow_next() {
    ux_flow_next();
}

void flow_prev() {
    ux_flow_prev();
}

void debug_display() {
    explicit_bzero(&global, sizeof(global));
    global.dynamic_flow = step_test;
    global.max = 10;
    ux_flow_init(0, dynamic_test_flow, NULL);
}
