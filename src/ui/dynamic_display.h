#pragma once

#include "ux.h"

enum e_state {
    STATIC_SCREEN,
    DYNAMIC_SCREEN,
};

typedef struct DynamicDisplay {
    enum e_state current_state;  // internal state management
    char title[32];              // to be set by the dynamic_flow callback
    char text[128];              // to be set by the dynamic_flow callback
    int index;  // current index of the flow state, will align with what is passed into dynamic_flow
    int max;    // the number of steps you need for your display, must be set before flow execution.
    int (*dynamic_flow)(int);  // dynamic_flow will be called by "step_generic" and pass in the step
                               // index. index will be between 0 and max-1
} DynamicDisplay;

// defined in dynamic_display.c
extern DynamicDisplay global;

extern const ux_flow_step_t step_upper_delimiter;
extern const ux_flow_step_t step_generic;
extern const ux_flow_step_t step_lower_delimiter;

// example implementation:
// UX_FLOW(dynamic_flow,
//        &step_welcome, //static ux
//
//        &step_upper_delimiter, // A special step that serves as the upper delimiter. It won't
//        print anything on the screen. &step_generic, // The generic step that will actually
//        display stuff on the screen. &step_lower_delimiter, // A special step that serves as the
//        lower delimiter. It won't print anything on the screen.
//
//        &step_quit, //static ux
//        FLOW_LOOP
//);

void debug_display();