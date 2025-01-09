#include QMK_KEYBOARD_H
#include "version.h"

#include "keycodes.h"

#include "g/keymap_combo.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif


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
  _______, SE_COMM, SE_W,    SE_F,    SE_P,    SE_B,    _______,         _______, SE_J,    SE_L,    SE_U,    SE_Y,    SE_DOT,  _______,
  _______, SE_A,    SE_R,    SE_S,    SE_T,    SE_G,                              SE_M,    SE_N,    SE_E,    SE_I,    SE_O,    _______,
  _______, SE_SLSH, SE_X,    SE_C,    SE_D,    SE_V,    _______,         _______, SE_K,    SE_H,    SE_LPRN, SE_RPRN, SE_UNDS, _______,
  _______, _______, _______, _______, KC_TAB,                                             KC_ENT, SAVE_VIM, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        				         MT_SPC,  KC_TAB, _______,         _______,    KC_ENT,  R_THMB
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
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, xxxxxxx, G(SE_W), G(SE_E), G(SE_R), xxxxxxx, _______,
  _______, xxxxxxx, xxxxxxx, DN_CTRL, xxxxxxx, xxxxxxx,                           xxxxxxx, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, xxxxxxx, KC_HOME, KC_PGUP, KC_END,   KC_END, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			            _______, _______, _______,         _______,    _______, _______
    ),
[_WNAV] = LAYOUT_ergodox_pretty(
  _______, G(SE_1), G(SE_2),    G(SE_3),   G(SE_4), G(SE_5), _______,         _______, G(SE_6), G(SE_7), G(SE_8), G(SE_9), _______, _______,
  _______, G(SE_Q), G(SE_COMM), G(SE_DOT), G(SE_P), xxxxxxx,_______,          _______, G(SE_J), G(SE_7), G(SE_8), G(SE_9), xxxxxxx, _______,
  _______, G(SE_W), G(SE_E),    G(SE_R),   G(SE_T), xxxxxxx,                           G(SE_H), G(SE_4), G(SE_5), G(SE_6), G(SE_L), _______,
  _______, xxxxxxx, G(SE_C),    xxxxxxx,   xxxxxxx, xxxxxxx, _______,         _______, G(SE_K), G(SE_1), G(SE_2), G(SE_3), xxxxxxx, _______,
  _______, _______, _______,    _______,   _______,                                             _______, _______, _______, _______, _______,
  					            _______,   _______,                           _______, _______,
				       			_______,                                               _______,
        			   G(KC_SPC), _______, _______,                           _______,  G(KC_M), G(KC_ENT)
    ),
[_SYM] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, TILD,    SE_PLUS, SE_ASTR, SE_EXLM,    CIRC, _______,         _______, _______, SE_7,    SE_8,    SE_9,    _______,  _______,
  _______, SE_PIPE, SE_LCBR, SE_RCBR, SE_MINS, SE_BSLS,                           _______, SE_4,    SE_5,    SE_6,    _______,  _______,
  _______, SE_QUES, SE_LABK, SE_RABK, SE_PERC,     GRV, _______,         _______, _______, SE_1,    SE_2,    SE_3,    _______, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______,  _______, SE_0
    ),
[_MODS] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,         _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,
  _______, _______, _______, _______, _______, _______,                           xxxxxxx, OS_GUI,  OS_CTRL, OS_SHFT, OS_ALT,  _______,
  _______, _______, _______, _______, _______, _______, _______,         _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, MY_RALT, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______, _______, _______
    ),
[_SHRT] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, C(SE_Q), C(SE_W), C(SE_E), C(SE_R), C(SE_T), _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, C(SE_A), C(SE_S), C(SE_D), C(SE_F), C(SE_G),                           _______, _______, _______, _______, _______, _______,
  _______, C(SE_Z), C(SE_X), C(SE_C), C(SE_V), C(SE_B), _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______, FUN, _______
    ),
[_FUN] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,         _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,
  _______, KC_F6,   KC_F4,   KC_F10,  KC_F2,   KC_F12,                            KC_F11,  KC_F3,   KC_F1,   KC_F5,   KC_F7,   _______,
  _______, xxxxxxx, xxxxxxx, xxxxxxx, KC_F8,   xxxxxxx, _______,         _______, xxxxxxx, KC_F9,   xxxxxxx, xxxxxxx, xxxxxxx, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			      _______, _______, _______,         _______, _______, _______
    ),
[_SPEC] = LAYOUT_ergodox_pretty(
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, SE_TILD, SYM_LQO, _______, SYM_RQO, _______, _______,         _______, _______, _______, _______, SE_CIRC, SE_DIAE, _______,
  _______, _______, SYM_LDQ, _______, SYM_RDQ, SE_ACUT,                           SE_GRV,  SYM_LFT, SYM_DWN, SYM_UP,  SYM_RHT, _______,
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
        			          _______, FUN, _______,         _______, _______, _______
    ),
};

void matrix_init_user(void) {

/* rgb_matrix_config.mode = RGB_MATRIX_TYPING_HEATMAP; */

rgb_matrix_enable();
rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);

}


// Combos

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home-row and other tight combos
        case escape_sym:
        case del:
        case dquo:
        case coln_sym:
        case quot:
        case split:
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
        case comb_ques:
        case comb_perc:
        case comb_grv:
        case comb_pipe:
        case comb_exlm:
        case comb_labk:
        case comb_rabk:
        case comb_lcbr:
        case arng:
        case adia:
        case odia:
        case eql:
        case gui_combo_l:
        case gui_combo_r:
        case ctrl_combo_l:
        case ctrl_combo_r:
        case close_win:
        case escape_sym:
        case split_vs:
        case split:
        case coln_sym:
        case dquo:
        case quot:
        case ent:
        case lalt:
            return false;
        default:
            return true;
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
