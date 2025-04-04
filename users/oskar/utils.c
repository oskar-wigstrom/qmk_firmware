#include "quantum.h"

#include "sm_td.h"
#include "keycodes.h"
#include "oneshot.h"
#include "tap_hold.h"
#include "casemodes.h"
#include "layermodes.h"
#include "leader.h"
#include "sm_td.h"

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// Keyboard utils

static uint16_t last_key_down = KC_NO;
static uint16_t last_key_up   = KC_NO;

static bool swap_caps_escape = false;
bool        is_caps_swapped(void) {
    return swap_caps_escape;
}

bool tap_undead_key(bool key_down, uint16_t code) {
    if (key_down) {
        tap_code16(code);
        tap_code16(KC_SPACE);
    }
    return false;
}

void swap_caps_esc(void) {
    swap_caps_escape = !swap_caps_escape;
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

void double_tap(uint16_t keycode) {
    tap_code16(keycode);
    tap_code16(keycode);
}

void double_tap_space(uint16_t keycode) {
    tap_code16(KC_SPC);
    double_tap(keycode);
    tap_code16(KC_SPC);
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
        case L_THMB_L:
        case R_THMB_R:
            return TAPPING_TERM + THUMB_TERM;
        default:
            return TAPPING_TERM;
    }
}
#endif

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
        case SPLIT_VS:
        case SPLIT:
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

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(HR_A, KC_A, KC_LEFT_ALT)
        SMTD_MT(HR_R, KC_R, KC_LEFT_GUI)
        SMTD_MT(HR_S, KC_S, KC_LEFT_CTRL)
        SMTD_MT(HR_T, KC_T, KC_LEFT_SHIFT)

        SMTD_MT(HR_O, KC_O, KC_LEFT_ALT)
        SMTD_MT(HR_I, KC_I, KC_RIGHT_GUI)
        SMTD_MT(HR_E, KC_E, KC_RIGHT_CTRL)
        SMTD_MT(HR_N, KC_N, KC_RIGHT_SHIFT)

        case LEADER_SYM:
            if (action == SMTD_ACTION_TAP) {
                start_leading();
            } else if (action == SMTD_ACTION_HOLD) {
                layer_move(_SYM);
            } else if (action == SMTD_ACTION_RELEASE) {
                layer_move(_BASE);
            }
            break;
    }
}
bool _process_record_user(uint16_t keycode, keyrecord_t *record) {
#if !defined(IS_ERGODOX) && !defined(IS_PLANCK)
#    error "This code is only for Ergodox or Planck keyboards"
#endif

    // Debugging
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
#    if defined(IS_ERGODOX)
        uprintf("E0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state), record->event.pressed, get_mods(), get_oneshot_mods(), record->tap.count);
#    elif defined(IS_PLANCK)
        uprintf("P0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state), record->event.pressed, get_mods(), get_oneshot_mods(), record->tap.count);
#    endif
    }
#endif

    if (!process_smtd(keycode, record)) {
        return false;
    }
    if (!process_leader(keycode, record)) {
        return false;
    }
    if (!process_num_word(keycode, record)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    if (!process_tap_hold(keycode, record)) {
        return false;
    }

    switch (keycode) {
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
            return tap_undead_key(record->event.pressed, SE_TILD);
        case CIRC:
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
                tap_code16(SE_COLN);
                return false;
            }
            break;
        case KC_ENT:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_NUM)) {
                    tap_code16(KC_PENT);
                } else {
                    tap_code16(KC_ENT);
                }
                disable_num_word();
            }
            return false;
        case TG_SWE:
            if (record->event.pressed) {
                layer_invert(_SWE);
            }
            return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_oneshot_pre(keycode, record);

    // If `false` was returned, then we did something special and should register that manually.
    // Otherwise register keyrepeat here by default.
    bool res = _process_record_user(keycode, record);

    process_oneshot_post(keycode, record);

    if (record->event.pressed) {
        last_key_down = keycode;
    } else {
        last_key_up = keycode;
    }

    return res;
}
