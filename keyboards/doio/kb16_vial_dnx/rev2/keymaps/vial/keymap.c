/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// OLED animation
#include "lib/layer_status/layer_status.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
    _FN1,
    _FN2,
    _FN3,
    _FN4,
    _FN5,
    _FN6,
    _FN7,
    _FN8,
    _FN9,
    _FN10
};

// Encoder MIDI CC keycodes and Grid MIDI keycodes
enum custom_keycodes {
    ENC1_CCW = SAFE_RANGE,
    ENC1_CW,
    ENC2_CCW,
    ENC2_CW,
    ENC3_CCW,
    ENC3_CW,
    ENC1_BTN,
    ENC2_BTN,
    ENC3_BTN,
    LAY_MOD,  // Layer navigation modifier (grid button KC_4)
    // Grid keys (16 keys) - sends CC 0-15 on layer 0, CC 16-31 on layer 1, etc.
    GRD_CC0,
    GRD_CC1,
    GRD_CC2,
    GRD_CC3,
    GRD_CC4,
    GRD_CC5,
    GRD_CC6,
    GRD_CC7,
    GRD_CC8,
    GRD_CC9,
    GRD_CC10,
    GRD_CC11,
    GRD_CC12,
    GRD_CC13,
    GRD_CC14,
    GRD_CC15,
};

// Send MIDI CC helper: channel 0, send single value
static inline void send_encoder_cc(uint8_t cc, uint8_t val);
// Encoder button toggle states
static bool enc1_btn_state = false;
static bool enc3_btn_state = false;
// Bottom row toggle states (positions 12-15)
static bool grd_cc12_state = false;
static bool grd_cc13_state = false;
static bool grd_cc14_state = false;
static bool grd_cc15_state = false;
// Layer navigation modifier state
static bool lay_mod_pressed = false;
#ifdef MIDI_ENABLE
extern MidiDevice midi_device;
static inline void send_encoder_cc(uint8_t cc, uint8_t val) {
    midi_send_cc(&midi_device, 0, cc, val);
}
#else
static inline void send_encoder_cc(uint8_t cc, uint8_t val) {
    (void)cc;
    (void)val;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │ 1 │ 2 │ 3 │ 4 │   │Ply│ │TO1│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │ 5 │ 6 │ 7 │ 8 │
       ├───┼───┼───┼───┤
       │ 9 │ 0 │ ↑ │Ent│      ┌───┐
       ├───┼───┼───┼───┤      │Mut│
       │Fn2│ ← │ ↓ │ → │      └───┘
       └───┴───┴───┴───┘
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │ ! │ @ │ # │ $ │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │ % │ ^ │ & │ * │
       ├───┼───┼───┼───┤
       │ ( │ ) │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4       */
    [_FN] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4       */
    [_FN1] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │Spi│Spd│   │   │   │   │ │TO0│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │Sai│Sad│   │   │
       ├───┼───┼───┼───┤
       │Tog│Mod│Hui│   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │Vai│Hud│Vad│      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        */
    [_FN2] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN3] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN4] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN5] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN6] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN7] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN8] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN9] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),

    [_FN10] = LAYOUT(
                LAY_MOD,  GRD_CC1,  GRD_CC2,  GRD_CC3,  ENC1_BTN,
                GRD_CC4,  GRD_CC5,  GRD_CC6,  GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9,  GRD_CC10, GRD_CC11, ENC3_BTN,
                GRD_CC12, GRD_CC13, GRD_CC14, GRD_CC15
            ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Layer nav modifier: track press/release
        case LAY_MOD:
            lay_mod_pressed = record->event.pressed;
            return false;
        
        // Encoder rotation: only on press
        case ENC1_CCW:
        case ENC1_CW:
        case ENC2_CCW:
        case ENC2_CW:
        case ENC3_CCW:
        case ENC3_CW:
            if (!record->event.pressed) return true;
            break;
        
        // Encoder buttons: handle both press and release
        case ENC1_BTN:
        case ENC2_BTN:
        case ENC3_BTN:
            break;
        
        // Grid keys: handle both press and release
        case GRD_CC0 ... GRD_CC15:
            break;
        
        default:
            return true;
    }

    switch (keycode) {
        // Encoder 1 (top left) - layer-aware CC
        // OR layer navigation 0-5 if LAY_MOD is held
        case ENC1_CCW: 
            if (lay_mod_pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer <= 5) {
                    layer_move(current_layer == 0 ? 5 : current_layer - 1);
                } else {
                    layer_move(5);  // Jump to layer 5 if outside range
                }
            } else {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 16 + (current_layer * 32);  // CC offset per layer
                send_encoder_cc(cc, 127);
            }
            return false;
        case ENC1_CW:  
            if (lay_mod_pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer <= 5) {
                    layer_move((current_layer + 1) % 6);
                } else {
                    layer_move(0);  // Jump to layer 0 if outside range
                }
            } else {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 16 + (current_layer * 32);
                send_encoder_cc(cc, 1);
            }
            return false;
        
        // Encoder 2 (top right) - layer-aware CC
        // OR layer navigation 6-11 if LAY_MOD is held
        case ENC2_CCW: 
            if (lay_mod_pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer >= 6 && current_layer <= 11) {
                    layer_move(current_layer == 6 ? 11 : current_layer - 1);
                } else {
                    layer_move(11);  // Jump to layer 11 if outside range
                }
            } else {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 17 + (current_layer * 32);
                send_encoder_cc(cc, 127);
            }
            return false;
        case ENC2_CW:  
            if (lay_mod_pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer >= 6 && current_layer <= 11) {
                    layer_move(6 + ((current_layer - 6 + 1) % 6));
                } else {
                    layer_move(6);  // Jump to layer 6 if outside range
                }
            } else {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 17 + (current_layer * 32);
                send_encoder_cc(cc, 1);
            }
            return false;
        
        // Encoder 3 (large center) - layer-aware CC
        case ENC3_CCW: 
            {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 18 + (current_layer * 32);
                send_encoder_cc(cc, 65);
            }
            return false;
        case ENC3_CW:  
            {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 18 + (current_layer * 32);
                send_encoder_cc(cc, 1);
            }
            return false;
        
        // Encoder button presses: toggle state on press only (layer-aware CC)
        case ENC1_BTN:
            if (record->event.pressed) {
                enc1_btn_state = !enc1_btn_state;
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 19 + (current_layer * 32);
                send_encoder_cc(cc, enc1_btn_state ? 127 : 0);
            }
            return false;
        case ENC2_BTN:
            {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 20 + (current_layer * 32);
                if (record->event.pressed) {
                    send_encoder_cc(cc, 127);
                } else {
                    send_encoder_cc(cc, 0);
                }
            }
            return false;
        case ENC3_BTN:
            if (record->event.pressed) {
                enc3_btn_state = !enc3_btn_state;
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = 21 + (current_layer * 32);
                send_encoder_cc(cc, enc3_btn_state ? 127 : 0);
            }
            return false;
        
        // Grid keys: simple sequential CC (0-15) with layer offset
        case GRD_CC0 ... GRD_CC15:
            {
                uint8_t base_cc = keycode - GRD_CC0;  // 0-15
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t cc = base_cc + (current_layer * 16);  // Layer 0: 0-15, Layer 1: 16-31, etc.
                
                // Bottom row (12-15) uses toggle behavior
                if (base_cc >= 12 && base_cc <= 15) {
                    if (record->event.pressed) {
                        // Toggle the state on press only
                        switch(base_cc) {
                            case 12: grd_cc12_state = !grd_cc12_state; send_encoder_cc(cc, grd_cc12_state ? 127 : 0); break;
                            case 13: grd_cc13_state = !grd_cc13_state; send_encoder_cc(cc, grd_cc13_state ? 127 : 0); break;
                            case 14: grd_cc14_state = !grd_cc14_state; send_encoder_cc(cc, grd_cc14_state ? 127 : 0); break;
                            case 15: grd_cc15_state = !grd_cc15_state; send_encoder_cc(cc, grd_cc15_state ? 127 : 0); break;
                        }
                    }
                } else {
                    // All other positions use momentary behavior
                    uint8_t val = record->event.pressed ? 127 : 0;
                    send_encoder_cc(cc, val);
                }
            }
            return false;
    }

    return true;
}

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN]   = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN1]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN2]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN3]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN4]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN5]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN6]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN7]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN8]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN9]  = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
    [_FN10] = { ENCODER_CCW_CW(ENC1_CCW, ENC1_CW), ENCODER_CCW_CW(ENC2_CCW, ENC2_CW), ENCODER_CCW_CW(ENC3_CCW, ENC3_CW) },
};
#endif
