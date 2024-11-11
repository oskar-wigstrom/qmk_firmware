#include <stdint.h>
#include "quantum.h"

#include "keycodes.h"
#include "status.h"
#include "oneshot.h"
#include "casemodes.h"
#include "layermodes.h"
#include "tap_hold.h"
#include "repeat.h"
#include "roll.h"
#include "leader.h"

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// Keyboard utils

static uint16_t last_key_down = KC_NO;
static uint16_t last_key_up   = KC_NO;

static bool linux_mode = true;
bool in_linux(void) {
    return linux_mode;
}

static bool swap_caps_escape = false;
bool is_caps_swapped(void) {
    return swap_caps_escape;
}

bool tap_undead_key(bool key_down, uint16_t code) {
    if (key_down) {
        tap_code16(code);
        tap_code16(KC_SPACE);
    }
    return false;
}

void tap16_repeatable(uint16_t keycode) {
    tap_code16(keycode);
    register_key_to_repeat(keycode);
}

void swap_caps_esc(void) {
    swap_caps_escape = !swap_caps_escape;
#ifdef OLED_DRIVER_ENABLE
    oled_on();
#endif
}

void tg_nix(void) {
    linux_mode = !linux_mode;
#ifdef OLED_DRIVER_ENABLE
    oled_on();
#endif
}

bool process_caps(bool key_down) {
    if (swap_caps_escape) {
        if (key_down) {
            register_code(KC_ESC);
        } else {
            unregister_code(KC_ESC);
        }
        return false;
    }
    return true;
}

bool process_escape(bool key_down) {
    if (swap_caps_escape) {
        if (key_down) {
            register_code(KC_CAPS);
        } else {
            unregister_code(KC_CAPS);
        }
        return false;
    }
    return true;
}

void tap_escape(void) {
    tap_code(swap_caps_escape ? KC_CAPS : KC_ESC);
}

void tap_caps_lock(void) {
    tap_code(swap_caps_escape ? KC_ESC : KC_CAPS);
}

void tap_space_shift(uint16_t key, bool key_down) {
    if (key_down) {
        tap_code16(key);
        tap_code(KC_SPC);
        set_oneshot_mods(MOD_BIT(KC_LSFT));
    }
}

void double_tap(uint16_t keycode) {
    tap_code16(keycode);
    tap_code16(keycode);
}

void double_tap_space(uint16_t keycode) {
    tap_code16(KC_SPC);
    double_tap(keycode);
    tap_code16(KC_SPC);
}

uint16_t corresponding_swe_key(uint16_t keycode) {
    switch (keycode) {
        case SE_LPRN:
            return SE_ARNG;
        case SE_ARNG:
            return SE_LPRN;
        case SE_RPRN:
            return SE_ADIA;
        case SE_ADIA:
            return SE_RPRN;
        case SE_UNDS:
            return SE_ODIA;
        case SE_ODIA:
            return SE_UNDS;
        default:
            return KC_NO;
    }
}


bool combo_should_trigger(uint16_t combo_index, combo_t *combo) {
    // FIXME this doesn't seem to work?
    return true;
}

// Tapping terms
#ifdef TAPPING_TERM_PER_KEY

#    define THUMB_TERM 20
#    define INDEX_TERM -20
#    define MIDDLE_TERM 0
#    define RING_TERM 80
#    define PINKY_TERM 180

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_SPC:
            return TAPPING_TERM + THUMB_TERM;
        case DN_CTRL:
            return TAPPING_TERM + MIDDLE_TERM;
        default:
            return TAPPING_TERM;
    }
}
#endif

// Case modes

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case REPEAT:
        case REV_REP:
            return false;
        case SE_A ... SE_Z:
        case SE_1 ... SE_0:
        case SE_ARNG:
        case SE_ADIA:
        case SE_ODIA:
        case SE_MINS:
        case SE_UNDS:
        case KC_BSPC:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                return true;
            }
            break;
    }
    return false;
}

void triple_tap(uint16_t keycode) {
    tap_code16(keycode);
    tap_code16(keycode);
    tap_code16(keycode);
}

void double_parens_left(uint16_t left, uint16_t right) {
    tap_code16(left);
    tap_code16(right);
    tap_code16(KC_LEFT);
}

// One-shot mods

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case CLEAR:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case CLEAR:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_GUI:
        case VIM_TMUX_SP:
        case VIM_TMUX_VS:
        case TAB_MOD:
            return true;
        default:
            return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_gui_state  = os_up_unqueued;

void process_oneshot_pre(uint16_t keycode, keyrecord_t *record) {
    update_oneshot_pre(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot_pre(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot_pre(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot_pre(&os_gui_state, KC_LGUI, OS_GUI, keycode, record);
}

void process_oneshot_post(uint16_t keycode, keyrecord_t *record) {
    update_oneshot_post(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot_post(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot_post(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot_post(&os_gui_state, KC_LGUI, OS_GUI, keycode, record);
}

void process_oneshot_key(uint16_t keycode, keyrecord_t *record) {
    update_oneshot_pre(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot_post(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
}

// Tap hold

bool tap_hold(uint16_t keycode) {
    switch (keycode) {
        case SE_DQUO:
        case SE_LABK:
        case SE_RABK:
        case SE_DOT:
        case SE_PERC:
        case GRV:
        case SE_AT:
        case SE_PIPE:
        case SE_EXLM:
        case SE_AMPR:
        case SE_QUES:
        case SE_HASH:
        case SE_LPRN:
        case SE_RPRN:
        case SE_LCBR:
        case SE_LBRC:
        case SE_EQL:
        case SE_UNDS:
        case SE_1:
        case SE_2:
        case SE_3:
        case SE_4:
        case SE_5:
        case SE_6:
        case G(SE_0):
        case G(SE_1):
        case G(SE_2):
        case G(SE_3):
        case G(SE_4):
        case G(SE_5):
        case G(SE_6):
        case G(SE_7):
        case G(SE_8):
        case G(SE_9):
        case G(SE_K):
        case G(SE_J):
        case G(SE_W):
        case G(SE_E):
        case G(SE_R):
        case G(SE_C):
        case SE_A ... SE_Z:
        case SE_ARNG:
        case SE_ADIA:
        case SE_ODIA:
        case E_ACUT:
        case CLOSE_WIN:
        case C(SE_A):
        case C(SE_C):
        case C(SE_W):
        case C(SE_F):
        case C(SE_E):
        case C(SE_R):
        case C(SE_S):
        case C(SE_T):
        case C(SE_H):
        case C(SE_X):
        case C(SE_V):
        case C(SE_G):
        case C(SE_D):
        case C(SE_B):
        case VIM_TMUX_SP:
        case VIM_TMUX_VS:
            return true;
        default:
            return false;
    }
}

void tap_hold_send_tap(uint16_t keycode) {
    switch (keycode) {
        case GRV:
            register_key_to_repeat(keycode);
            tap_undead_key(true, SE_GRV);
            return;
        case E_ACUT:
            tap_code16(SE_ACUT);
            tap_code16(SE_E);
            return;
        case CLOSE_WIN:
            tap_code16(C(SE_W));
            tap_code(SE_Q);
            /* tap_escape(); */
            /* tap_code16(SE_COLN); */
            /* tap_code(SE_Q); */
            /* tap_code(KC_ENT); */
            return;
        case VIM_TMUX_SP:
            tap_code16(C(SE_W));
            tap_code(SE_S);
            return;
        case VIM_TMUX_VS:
            tap_code16(C(SE_W));
            tap_code(SE_V);
            return;
        default:
            tap16_repeatable(keycode);
    }
}

void tap_hold_send_hold(uint16_t keycode) {
    disable_caps_word();

    switch (keycode) {
        case SE_SLSH:
        case SE_LABK:
        case SE_RABK:
            // FIXME should be repeatable
            double_tap(keycode);
            return;
        case SE_DQUO:
        case SE_0:
            triple_tap(keycode); // Can be changed
            return;
        case GRV:
            tap_undead_key(true, SE_GRV);
            tap_undead_key(true, SE_GRV);
            tap_undead_key(true, SE_GRV);
            return;
        case SE_PIPE:
        case SE_AMPR:
        case SE_EQL:
            double_tap_space(keycode);
            return;
        case SE_UNDS:
            tap_code16(SE_MINS);
            return;
        case SE_DOT:
            tap_code16(SE_COMM);
            return;
        case SE_LPRN:
            tap_code16(SE_LBRC);
            return;
        case SE_RPRN:
            tap_code16(SE_RBRC);
            return;
        case SE_1:
            tap_code16(SE_EXLM);
            return;
        case SE_2:
            tap_code16(SE_AT);
            return;
        case SE_3:
            tap_code16(SE_HASH);
            return;
        case SE_4:
            tap_code16(SE_DLR);
            return;
        case SE_5:
            tap_code16(SE_PERC);
            return;
        case SE_6:
            tap_code16(SE_AMPR);
            return;
        case E_ACUT:
            tap_code16(SE_ACUT);
            tap_code16(S(SE_E));
            return;
        case CLOSE_WIN:
            tap16_repeatable(S(G(SE_C)));
            return;
        case VIM_TMUX_SP:
            tap_code16(C(SE_B));
            send_string("\"");
            return;
        case VIM_TMUX_VS:
            tap_code16(C(SE_B));
            send_string("%");
            return;
        default:
            tap16_repeatable(S(keycode));
    }
}

uint16_t tap_hold_timeout(uint16_t keycode) {
    switch (keycode) {
        // Extra
        case CLOSE_WIN:
            return 180;
        // Thumb
        // No key here.
        // Pinky
        case SE_Q:
        case SE_A:
        case SE_Z:
        case SE_DOT:
        case SE_O:
        case SE_UNDS:
        case SE_ODIA:
            return 155;
        // Ring
        case SE_W:
        case SE_R:
        case SE_X:
        case SE_Y:
        case SE_I:
        case SE_RPRN:
        case SE_ADIA:
        case C(SE_9):
        case C(SE_6):
        case C(SE_3):
            return 125;
        // Middle
        case SE_F:
        case SE_S:
        case SE_C:
        case SE_U:
        case SE_E:
        case SE_LPRN:
        case SE_ARNG:
        case SE_8:
        case SE_5:
        case SE_2:
            return 120;
        // Slow index
        // Non here at the moment
        // Index
        default:
            return 120;
    }
}

// https://github.com/andrewjrae/kyria-keymap#userspace-leader-sequences
void *leader_toggles_func(uint16_t keycode) {
    switch (keycode) {
        case KC_N:
            layer_invert(_NUM);
            return NULL;
        case KC_S:
            layer_invert(_SYM);
            return NULL;
        case KC_C:
            swap_caps_esc();
            return NULL;
        default:
            return NULL;
    }
}

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case KC_T:
            return leader_toggles_func;
        case KC_C:
            tap_caps_lock();
            return NULL;
        case ESC_SYM:
            tap_code16(C(S(KC_ESC)));
            return NULL;
        default:
            return NULL;
    }
}

bool _process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Error: Too many arguments for format. Meh!
    // #ifdef CONSOLE_ENABLE
    //     if (record->event.pressed) {
    //         uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
    //              keycode,
    //              record->event.key.row,
    //              record->event.key.col,
    //              get_highest_layer(layer_state),
    //              record->event.pressed,
    //              get_mods(),
    //              get_oneshot_mods(),
    //              record->tap.count
    //              );
    //     }
    // #endif

    if (!process_leader(keycode, record)) {
        return false;
    }
    if (!process_num_word(keycode, record)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    if (!process_roll(keycode, record)) {
        return false;
    }
    if (!process_tap_hold(keycode, record)) {
        // Extra register here to allow fast rolls without waiting for tap hold,
        // (which will also overwrite this).
        if (record->event.pressed) {
            register_key_to_repeat(keycode);
        }
        return false;
    }

    switch (keycode) {
        case ESC_SYM:
            if (record->tap.count && record->event.pressed) {
                tap_escape();
                return false;
            }
            break;
        case KC_CAPS:
            return process_caps(record->event.pressed);
        case CLEAR:
            clear_oneshot_mods();
            if (get_oneshot_layer() != 0) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            stop_leading();
            layer_off(_NUM);
            layer_off(_SYM);
            layer_move(_BASE);
            return false;
        case CANCEL:
            layer_off(_NUM);
            layer_off(_SYM);
            stop_leading();
            // disable_gaming();
            return false;
        case TILD:
            register_key_to_repeat(TILD);
            return tap_undead_key(record->event.pressed, SE_TILD);
        case CIRC:
            register_key_to_repeat(CIRC);
            return tap_undead_key(record->event.pressed, SE_CIRC);
        case NUMWORD:
            process_num_word_activation(record);
            return false;
        case CAPSWORD:
            if (record->event.pressed) {
                enable_caps_word();
            }
            return false;
        case SAVE_VIM:
            if (record->event.pressed) {
                tap_escape();
                tap_code16(SE_COLN);
                tap_code(SE_W);
                tap_code(KC_ENT);
            }
            return false;
        case NUM_G:
            if (record->event.pressed) {
                tap_code16(S(SE_G));
            }
            return false;
        case COLN_SYM:
            if (record->tap.count && record->event.pressed) {
                tap16_repeatable(SE_COLN);
                return false;
            }
            break;
        case KC_ENT:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_NUM)) {
                    tap16_repeatable(KC_PENT);
                } else {
                    tap16_repeatable(KC_ENT);
                }
                disable_num_word();
            }
            return false;
        case TG_SWE:
            if (record->event.pressed) {
                uint16_t swe_key = corresponding_swe_key(last_key());
                if (swe_key != KC_NO) {
                    tap_code16(KC_BSPC);
                    tap_code16(swe_key);
                }
                layer_invert(_SWE);
            }
            return false;
        case LEADER:
            start_leading();
            return false;
        case REPEAT:
            // Enable fast UI rolls with repeat key
            end_tap_hold();
            update_repeat_key(record);
            return false;
        case REV_REP:
            update_reverse_repeat_key(record);
            return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_oneshot_pre(keycode, record);

    // If `false` was returned, then we did something special and should register that manually.
    // Otherwise register keyrepeat here by default.
    bool res = _process_record_user(keycode, record);

    // Space needs some special handling to not interfere with NAV toggling.
    // Maybe there's a more general way to do this, but I dunno.
    if (keycode == MT_SPC) {
        if (!record->event.pressed && last_key_down == MT_SPC) {
            register_key_to_repeat(KC_SPC);
        }
    } else if (res && record->event.pressed) {
        register_key_to_repeat(keycode);
    }

    process_oneshot_post(keycode, record);

    if (record->event.pressed) {
        last_key_down = keycode;
    } else {
        last_key_up = keycode;
    }

    return res;
}

void matrix_scan_user(void) {
    tap_hold_matrix_scan();
}
