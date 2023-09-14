/*****************************************************************************
 *   Accumulate Ledger Wallet
 *   (c) 2022 DefiDevs, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#include "menu.h"

#include "../globals.h"
#include "glyphs.h"
#include "os.h"
#include "ux.h"
#include "../dynamic_display.h"

UX_STEP_NOCB(ux_menu_ready_step, pnn, {&C_accumulate_logo, "Accumulate", "is ready"});
UX_STEP_NOCB(ux_menu_version_step, bn, {"Version", APPVERSION});
UX_STEP_CB(ux_menu_settings_step, pb, ui_menu_settings(), {&C_icon_coggle, "Settings"});
UX_STEP_CB(ux_menu_about_step, pb, ui_menu_about(), {&C_icon_certificate, "About"});
UX_STEP_VALID(ux_menu_exit_step, pb, os_sched_exit(-1), {&C_icon_dashboard_x, "Quit"});
//UX_STEP_CB(ux_idle_flow_2_step,
//           pb,
//           ux_menulist_init(0, settings_submenu_getter, settings_submenu_selector),
//           {
//               &C_icon_coggle,
//               "Settings",
//           });

// FLOW for the main menu:
// #1 screen: ready
// #2 screen: version of the app
// #3 screen: about submenu
// #4 screen: quit
UX_FLOW(ux_menu_main_flow,
        &ux_menu_ready_step,
        &ux_menu_version_step,
        &ux_menu_about_step,
        &ux_menu_settings_step,
        &ux_menu_exit_step,
        FLOW_LOOP);

void ui_menu_main() {
    if (G_ux.stack_count == 0) {
        ux_stack_push();
    }

    ux_flow_init(0, ux_menu_main_flow, NULL);
}

UX_STEP_NOCB(ux_menu_info_step, bn, {"Accumulate App", "(c) 2023 DefiDevs"});

UX_STEP_CB(ux_menu_back_step, pb, ui_menu_main(), {&C_icon_back, "Back"});

// FLOW for the about submenu:
// #1 screen: app info
// #2 screen: back button to main menu
UX_FLOW(ux_menu_about_flow, &ux_menu_info_step, &ux_menu_back_step, FLOW_LOOP);

void ui_menu_about() {
    ux_flow_init(0, ux_menu_about_flow, NULL);
}

void ui_display_blind_signing_enable();

UX_STEP_CB(ux_menu_back_settings_step, pb, ui_menu_settings(), {&C_icon_back, "Back"});
UX_STEP_CB(ux_menu_settings_blind_signing_step, pb,ui_display_blind_signing_enable(), {&C_icon_eye, global.title});

// FLOW for the menu settings submenu:
// #! screen: Blind Signing Enable/Disable
// #2 screen: back button to the main menu
UX_FLOW(ux_menu_settings_flow,
        &ux_menu_settings_blind_signing_step,
        &ux_menu_back_step, FLOW_LOOP);
// Step with icon and text

UX_STEP_NOCB(ux_menu_enable_blind_signing_begin_step,
             pnn,
             {
                 &C_icon_warning,
                 "Blind Signing",
                 global.title,
             });

void toggleBlindSigning();
UX_STEP_CB(ux_menu_blind_signing_toggle_step,
           pb,
           toggleBlindSigning(),
           {
               &C_icon_validate_14,
               global.text,
           });


UX_FLOW(ux_menu_enable_blind_signing_flow,
        &ux_menu_enable_blind_signing_begin_step,  // static ux
        &ux_menu_blind_signing_toggle_step,
        &ux_menu_back_settings_step,
        FLOW_LOOP);

void ui_menu_settings() {
    snprintf(global.title, sizeof(global.title), "Blind Signing (%s)",
             G_settings_context.blind_signing_enabled?"on":"off");
    ux_flow_init(0, ux_menu_settings_flow, NULL);
}


void toggleBlindSigning() {
    G_settings_context.blind_signing_enabled ^= 1;
    ui_menu_settings();
}

void ui_display_blind_signing_enable() {
    if (G_settings_context.blind_signing_enabled) {
        snprintf(global.title, sizeof(global.title), "is Enabled");
        snprintf(global.text, sizeof(global.text), "Disable");
    } else {
        snprintf(global.title, sizeof(global.title), "is Disabled");
        snprintf(global.text, sizeof(global.text), "Enable");
    }
    ux_flow_init(0, ux_menu_enable_blind_signing_flow, NULL);
}
