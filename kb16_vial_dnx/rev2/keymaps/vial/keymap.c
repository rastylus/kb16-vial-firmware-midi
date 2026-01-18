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
    _FN2
};

// Encoder MIDI CC keycodes
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
};

// Send MIDI CC helper: channel 0, send single value
static inline void send_encoder_cc(uint8_t cc, uint8_t val);
// Encoder button toggle states
static bool enc1_btn_state = false;
static bool enc3_btn_state = false;
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
                KC_1,     KC_2,    KC_3,    KC_4,     ENC1_BTN,
                KC_5,     KC_6,    KC_7,    KC_8,     TO(_FN),
                KC_9,     KC_0,    KC_UP,   KC_ENT,   ENC3_BTN,
                MO(_FN2), KC_LEFT, KC_DOWN, KC_RIGHT
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
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, TO(_FN1),
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
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, TO(_FN2),
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
                RGB_SPI, RGB_SPD, _______, QK_BOOT, _______,
                RGB_SAI, RGB_SAD, _______, _______, TO(_BASE),
                RGB_TOG, RGB_MOD, RGB_HUI, _______, _______,
                _______, RGB_VAI, RGB_HUD, RGB_VAD
            ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
        
        default:
            return true;
    }

    switch (keycode) {
        // Encoder 1 (top left) CC16: CW +1, CCW -1 (symmetric)
        case ENC1_CCW: send_encoder_cc(16, 127); return false;
        case ENC1_CW:  send_encoder_cc(16, 1);   return false;
        // Encoder 2 (top right) CC17: CW +1, CCW -1 (symmetric)
        case ENC2_CCW: send_encoder_cc(17, 127); return false;
        case ENC2_CW:  send_encoder_cc(17, 1);   return false;
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
        case ENC3_BTN:
            if (record->event.pressed) {
                enc3_btn_state = !enc3_btn_state;
                send_encoder_cc(21, enc3_btn_state ? 127 : 0);
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
};
#endif
