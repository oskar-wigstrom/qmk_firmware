#include <stdint.h>
#include QMK_KEYBOARD_H
#include "version.h"

#include "keycodes.h"
#include "leader.h"

#include "g/keymap_combo.h"

#define MAX_DEFERRED_EXECUTORS 10

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[_BASE] = LAYOUT_ergodox_pretty(
  _______, SE_1,    SE_2,    SE_3,    SE_4,    SE_5,    _______,         _______, SE_6,    SE_7,    SE_8,    SE_9,    SE_0,    _______,
  _______, SE_Q,    SE_W,    SE_F,    SE_P,    SE_B,    _______,         _______, SE_J,    SE_L,    SE_U,    SE_Y,    SE_QUOT,  _______,
  _______, HR_A,    HR_R,    HR_S,    HR_T,    SE_G,                              SE_M,    HR_N,    HR_E,    HR_I,    HR_O,    _______,
  _______, SE_Z,    SE_X,    SE_C,    SE_D,    SE_V,    _______,         _______, SE_K,    SE_H,    SE_COMM, SE_DOT,  SE_SLSH, _______,
  _______, CAPS_WORD, _______, _______, L_TMB_L,                                             KC_BSPC, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        				         L_TMB_M,  L_TMB_R, _______,         _______,    LEADER,  R_TMB_M
      ),
[_SWE] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, SE_ARNG, SE_ADIA, SE_ODIA, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______, _______, _______
    ),
[_NAV] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______,    REDO,   PASTE,    COPY,    CUT,     UNDO, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                           KC_CAPS, KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______,  KC_INS, KC_HOME, KC_PGUP, KC_END,   KC_END, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			            _______, _______, _______,         _______,    _______, _______
    ),
[_NUM] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, _______, SE_7,    SE_8,    SE_9,    _______,  _______,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, xxxxxxx,                           SE_PLUS, SE_4,    SE_5,    SE_6,    _______, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, SE_MINS, SE_1,    SE_2,    SE_3,    _______,  _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______,   SE_BSLS, SE_0
    ),
[_SNUM] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, _______,    CIRC, SE_DQUO, SE_COLN,    _______,  _______,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, xxxxxxx,                           _______,  SE_DLR, SE_PERC, SE_AMPR,    _______, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, SE_UNDS, SE_EXLM,   SE_AT, SE_HASH,    _______,  _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______,   SE_PIPE, SE_EQL
    ),
[_SYM] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, TILD,    SE_LBRC, SE_RBRC, _______, _______, _______,         _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,
  _______, SE_LPRN, SE_LCBR, SE_RCBR, SE_RPRN, _______,                           xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,
  _______, _______, SE_LABK, SE_RABK, _______, _______, _______,         _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,  _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______,   _______, _______
    ),
};
// clang-format on
void matrix_init_user(void) {
    /* rgb_matrix_config.mode = RGB_MATRIX_TYPING_HEATMAP; */

    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
}

void set_led(uint8_t id, bool on) {
    if (id == 0) {
        if (on) {
            ergodox_right_led_1_on();
        } else {
            ergodox_right_led_1_off();
        }
    } else if (id == 1) {
        if (on) {
            ergodox_right_led_2_on();
        } else {
            ergodox_right_led_2_off();
        }
    } else if (id == 2) {
        if (on) {
            ergodox_right_led_3_on();
        } else {
            ergodox_right_led_3_off();
        }
    }
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _BASE:
            break;
        case _NAV:
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

    return state;
};
