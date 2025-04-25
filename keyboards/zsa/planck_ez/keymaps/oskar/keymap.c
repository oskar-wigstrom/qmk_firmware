/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include <stdint.h>
#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "utils.h"

#include "g/keymap_combo.h"

#if MAX_DEFERRED_EXECUTORS < 10
#    error "MAX_DEFERRED_EXECUTORS must be at least 10"
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer: Modified RSTHD
     */
    [_BASE] = LAYOUT_planck_1x2uC(
      SE_COMM, SE_W,    SE_F,    SE_P,    SE_B,   _______,  _______,   SE_J,    SE_L,    SE_U,    SE_Y,    SE_DOT,
      HR_A,    HR_R,    HR_S,    HR_T,    SE_G,   _______,  _______,   SE_M,    HR_N,    HR_E,    HR_I,    HR_O,
      SE_SLSH, SE_X,    SE_C,    SE_D,    SE_V,   _______,  _______,   SE_K,    SE_H,    SE_LPRN, SE_RPRN, SE_UNDS,
      _______, _______, KC_ESC, L_THMB_L, L_THMB_R, _______,             R_THMB_L, R_THMB_R, KC_BSPC, _______, _______
    ),
    [_SWE]  = LAYOUT_planck_1x2uC(
      _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,  _______,  _______, _______, SE_ARNG, SE_ADIA, SE_ODIA,
      _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______
    ),
    [_NAV]  = LAYOUT_planck_1x2uC(
      xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,  _______,  xxxxxxx, G(SE_W), G(SE_E), G(SE_R), xxxxxxx,
      xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,  _______,  xxxxxxx, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
      xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,  _______,  xxxxxxx, KC_HOME, KC_PGUP, KC_END,   KC_END,
      _______, _______, _______, _______, _______,  _______,            _______,    _______, _______, _______, _______
    ),
    [_WNAV] = LAYOUT_planck_1x2uC(
      G(SE_Q), G(SE_COMM), G(SE_DOT), G(SE_P), xxxxxxx,   _______, _______, G(SE_J), G(SE_7),   G(SE_8), G(SE_9), xxxxxxx,
      G(SE_T), G(SE_W),    G(SE_E),   G(SE_R), xxxxxxx,   _______, _______, G(SE_H), G(SE_4),   G(SE_5), G(SE_6), G(SE_L),
      xxxxxxx, G(SE_C),    xxxxxxx,   xxxxxxx,   xxxxxxx,   _______, _______, G(SE_K), G(SE_1),   G(SE_2), G(SE_3), xxxxxxx,
      _______, _______,    _______,   G(KC_SPC),   _______, _______,          G(KC_M), G(KC_ENT), _______, _______, _______
    ),
    // Important that the symbols on the base layer have the same positions as these symbols
    [_SYM]  = LAYOUT_planck_1x2uC(
      TILD,    _______, SE_ASTR, SE_EXLM,    CIRC,  _______,  _______,   _______,    SE_7,    SE_8,    SE_9,  SE_MINS,
      SE_PIPE, SE_LCBR, SE_RCBR, _______, SE_BSLS,  _______,  _______,      AT_E,    SE_4,    SE_5,    SE_6,  SE_PLUS,
      SE_QUES, SE_LABK, SE_RABK, SE_PERC,     GRV,  _______,  _______,     SE_AT,    SE_1,    SE_2,    SE_3,  KC_DEL,
      _______, _______, _______, _______, _______,  _______,                _______, SE_0, _______, _______,  _______
    ),
};
// clang-format on

// Combos

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
            // Home-row and other tight combos
        case del:
        case dquo:
        case quot:
        case split:
        case gui_combo_l:
        case gui_combo_r:
            return COMBO_TERM;
            // Very relaxed
        case qe_comb:
        case split_vs:
            //        case gt_eq:
            return COMBO_TERM + 55;
        // Regular combos, slightly relaxed
        default:
            return COMBO_TERM + 25;
    }
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    switch (index) {
        case del:
        case comb_perc:
        case comb_grv:
        case comb_pipe:
        case comb_exlm:
        case comb_labk:
        case comb_rabk:
        case comb_lcbr:
        case comb_1:
        case comb_2:
        case comb_3:
        case comb_4:
        case comb_5:
        case comb_6:
        case arng:
        case adia:
        case odia:
        case eql:
        case gui_combo_l:
        case gui_combo_r:
        case close_win:
        case split_vs:
        case split:
        case coln_sym:
        case dquo:
            return false;
        default:
            return true;
    }
}

void set_led(uint8_t id, bool on) {
    if (id == 0) {
        planck_ez_left_led_on();
        planck_ez_left_led_level(127);
    } else if (id == 1) {
        planck_ez_right_led_on();
        planck_ez_right_led_level(127);
    }
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _BASE:
            break;
        case _NAV:
            planck_ez_right_led_on();
            planck_ez_right_led_level(127);
            break;
        default:
            break;
    }

    return state;
};
