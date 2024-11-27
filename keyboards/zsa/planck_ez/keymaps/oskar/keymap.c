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

#include QMK_KEYBOARD_H
#include "keycodes.h"

#include "g/keymap_combo.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer: Modified RSTHD
     */
    [_BASE] = LAYOUT_planck_1x2uC(
      SE_COMM, SE_W,    SE_F,    SE_P,    SE_B,   _______,  _______,   SE_J,    SE_L,    SE_U,    SE_Y,    SE_DOT,
      SE_A,    SE_R,    SE_S,    SE_T,    SE_G,   _______,  _______,   SE_M,    SE_N,    SE_E,    SE_I,    SE_O, //REPEAT rem.
      SE_SLSH, SE_X,    SE_C,    SE_D,    SE_V,   _______,  _______,   SE_K,    SE_H,    SE_LPRN, SE_RPRN, SE_UNDS,
      _______, _______, _______, _______,  MT_SPC, _______,             R_THMB, _______, _______, _______, _______
    ),
    [_SWE]  = LAYOUT_planck_1x2uC(
      _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,  _______,  _______, _______, SE_ARNG, SE_ADIA, SE_ODIA,
      _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______
    ),
    [_NAV]  = LAYOUT_planck_1x2uC(
      xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,  _______,  xxxxxxx, G(SE_W), G(SE_E), G(SE_R), xxxxxxx,
      xxxxxxx, xxxxxxx, DN_CTRL, xxxxxxx, xxxxxxx,  _______,  _______,  xxxxxxx, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
      xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,  _______,  xxxxxxx, KC_HOME, KC_PGUP, KC_END,   KC_END,
      _______, _______, _______, _______, _______,  _______,            _______,    _______, _______, _______, _______
    ),
    // Important that the symbols on the base layer have the same positions as these symbols
    [_SYM]  = LAYOUT_planck_1x2uC(
      TILD,    SE_PLUS, SE_ASTR, SE_EXLM,    CIRC,  _______,  _______,   _______, SE_7,    SE_8,    SE_9,    _______,
      SE_PIPE, SE_LCBR, SE_RCBR, SE_SLSH, SE_BSLS,  _______,  _______,   _______, SE_4,    SE_5,    SE_6,    _______,
      SE_COMM, SE_LABK, SE_RABK, SE_QUES,     GRV,  _______,  _______,   _______, SE_1,    SE_2,    SE_3,    _______,
      _______, _______, _______, _______, _______,  _______,             SE_0,    _______, _______, _______, _______
    ),
    [_MODS] = LAYOUT_planck_1x2uC(
      _______, _______, _______, _______, _______,  _______,  _______,   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,
      _______, _______, _______, _______, _______,  _______,  _______,   xxxxxxx, OS_GUI,  OS_CTRL, OS_SHFT, OS_ALT,
      _______, _______, _______, _______, _______,  _______,  _______,   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, MY_RALT,
      _______, _______, _______, _______, _______,  _______,             _______, _______, _______, _______, _______
    ),
    [_SHRT] = LAYOUT_planck_1x2uC(
      C(SE_Q), C(SE_W), C(SE_E), C(SE_R), C(SE_T),  _______,  _______,  _______, _______, _______, _______, _______,
      C(SE_A), C(SE_S), C(SE_D), C(SE_F), C(SE_G),  _______,  _______,  _______, _______, _______, _______, _______,
      C(SE_Z), C(SE_X), C(SE_C), C(SE_V), C(SE_B),  _______,  _______,  _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,  _______,            _______, FUN,     _______, _______, _______
    ),
    /*
    [_SHRT] = LAYOUT(
      C(SE_A), C(SE_C), C(SE_W), C(SE_F), C(SE_E),      _______, _______, _______, _______, _______,
      C(SE_R), C(SE_S), C(SE_T), C(SE_H), xxxxxxx,      _______, _______, _______, _______, _______,
      C(SE_X), C(SE_V), C(SE_G), C(SE_D), C(SE_B),      _______, _______, _______, _______, _______,
                                 _______, _______,      _______, FUN
    ),
    */
    [_FUN]  = LAYOUT_planck_1x2uC(
      xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,   _______,  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,
      KC_F6,   KC_F4,   KC_F10,  KC_F2,   KC_F12,    _______,  _______, KC_F11,  KC_F3,   KC_F1,   KC_F5,   KC_F7,
      xxxxxxx, xxxxxxx, xxxxxxx, KC_F8,   xxxxxxx,   _______,  _______, xxxxxxx, KC_F9,   xxxxxxx, xxxxxxx, xxxxxxx,
      _______, _______, _______, _______, _______,   _______,           _______, _______, _______, _______, _______
    ),
    [_SPEC] = LAYOUT_planck_1x2uC(
      SE_TILD, SYM_LQO, _______, SYM_RQO, _______,   _______,  _______, _______, _______, _______, SE_CIRC, SE_DIAE,
      _______, SYM_LDQ, _______, SYM_RDQ, SE_ACUT,   _______,  _______, SE_GRV,  SYM_LFT, SYM_DWN, SYM_UP,  SYM_RHT,
      _______, _______, _______, _______, _______,   _______,  _______, _______, _______, _______, _______, _______,
      _______, _______, _______, FUN,     _______,   _______,           _______, _______, _______, _______, _______
    )
};



// Combos

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home-row and other tight combos
        case ctrl_combo_l:
        case escape_sym:
        case del:
        case dquo:
        case coln_sym:
        case ctrl_combo_r:
        case quot:
        case vim_tmux_sp:
        case gui_combo_l:
        case gui_combo_r:
        case dlr:
            return COMBO_TERM;
        // Vertical combos, very relaxed
/*      case small_left_arrow:
        case lt_eq:
        case large_right_arrow:
        case small_right_arrow:
        case pipe_to: */
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
        case backsp:
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
        case ctrl_combo_l:
        case ctrl_combo_r:
        case shift_combo_l:
        case shift_combo_r:
        case close_win:
        case escape_sym:
        case split_vs:
        case split:
        case coln_sym:
        case dquo:
        case lalt:
        case win_alt:
            return false;
        default:
            return true;
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


