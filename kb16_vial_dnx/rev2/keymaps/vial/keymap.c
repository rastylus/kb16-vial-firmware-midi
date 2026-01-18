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
    // Grid keys (16 keys) - CC 0-15 (note: CC 0-31 are bank selectors, consider CC 32-47 or higher)
    GRD_CC0,
    GRD_CC1,
    GRD_CC2,
    GRD_CC4,  // Skip GRD_CC3 (replaced with LAY_MOD)
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
                GRD_CC0,  GRD_CC1, GRD_CC2, LAY_MOD,  ENC1_BTN,
                GRD_CC4,  GRD_CC5, GRD_CC6, GRD_CC7,  ENC2_BTN,
                GRD_CC8,  GRD_CC9, GRD_CC10, GRD_CC11, ENC3_BTN,
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
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
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
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
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
                RGB_SPI, RGB_SPD, _______, LAY_MOD, _______,
                RGB_SAI, RGB_SAD, _______, _______, ENC2_BTN,
                RGB_TOG, RGB_MOD, RGB_HUI, _______, _______,
                _______, RGB_VAI, RGB_HUD, RGB_VAD
            ),

    [_FN3] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN4] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN5] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN6] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN7] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN8] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN9] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    [_FN10] = LAYOUT(
                _______, _______, _______, LAY_MOD, _______,
                _______, _______, _______, _______, ENC2_BTN,
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
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
        // Encoder 1 (top left) CC16: CW +1, CCW -1 (symmetric)
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
                send_encoder_cc(16, 127);
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
                send_encoder_cc(16, 1);
            }
            return false;
        
        // Encoder 2 (top right) CC17: CW +1, CCW -1 (symmetric)
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
                send_encoder_cc(17, 127);
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
                send_encoder_cc(17, 1);
            }
            return false;
        
        // Encoder 3 (large center) CC18: CW +1, CCW gentle step (65) to avoid snapping
        case ENC3_CCW: send_encoder_cc(18, 65);  return false;
        case ENC3_CW:  send_encoder_cc(18, 1);   return false;
        
        // Encoder button presses: toggle state on press only
        case ENC1_BTN:
            if (record->event.pressed) {
                enc1_btn_state = !enc1_btn_state;
                send_encoder_cc(19, enc1_btn_state ? 127 : 0);
            }
            return false;
        case ENC2_BTN:
            if (record->event.pressed) {
                send_encoder_cc(20, 127);
            } else {
                send_encoder_cc(20, 0);
            }
            return false;
        case ENC3_BTN:
            if (record->event.pressed) {
                enc3_btn_state = !enc3_btn_state;
                send_encoder_cc(21, enc3_btn_state ? 127 : 0);
            }
            return false;
        
        // Grid keys CC 0-15 (skip 3): send 127 on press, 0 on release
        case GRD_CC0 ... GRD_CC15:
            {
                uint8_t cc_offset[] = {0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
                uint8_t cc = cc_offset[keycode - GRD_CC0];
                uint8_t val = record->event.pressed ? 127 : 0;
                send_encoder_cc(cc, val);
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
