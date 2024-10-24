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
  // left hand
  _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______,
  _______, SE_COMM, SE_W,    SE_F,    SE_P,    SE_B,    _______,         _______, SE_J,    SE_L,    SE_U,    SE_Y,   SE_DOT,   _______,
  _______, SE_A,    SE_R,    SE_S,    SE_T,    SE_G,                              SE_M,    SE_N,    SE_E,    SE_I,    SE_O,    _______,
  _______, SE_SLSH, SE_X,    SE_C,    SE_D,    SE_V,    _______,         _______, SE_K,    SE_H,    SE_LPRN, SE_RPRN, SE_UNDS, _______,
  _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______,
  					       _______, _______,         _______, _______,
				       			_______,	 _______,
  				      SHRT,    MT_SPC,  _______,         _______, R_THMB,  SPEC
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
        case ctrl_combo_l:
        case escape_sym:
        case tab_mod:
        case del:
        case dquo:
        case coln_sym:
        case ctrl_combo_r:
        case quot:
        case ent:
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
        case vim_tmux_vs:
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
        case q_comb:
        case qu_comb:
        case z_comb:
        case num:
        case comb_perc:
        case comb_grv:
        case comb_hash:
        case comb_pipe:
        case comb_ques:
        case comb_exlm:
        case comb_ampr:
        case comb_labk:
        case comb_rabk:
        case comb_lcbr:
        case comb_lbrc:
        case comb_at:
        case comb_0:
        case comb_e_acut:
//        case rev_rep:
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
        case tab_mod:
        case vim_tmux_vs:
        case vim_tmux_sp:
        case coln_sym:
        case dquo:
        case lalt:
        case win_alt:
            return false;
        default:
            return true;
    }
}


