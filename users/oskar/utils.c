#include "quantum.h"

#include "keycodes.h"
#include "sm_td.h"
#include "oneshot.h"
#include "leader.h"
#include "tap_hold.h"
#include "casemodes.h"
#include "layermodes.h"
#include "status.h"

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

void clear(void) {
    clear_oneshot_mods();
    if (get_oneshot_layer() != 0) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    stop_leading();
    disable_num_word();
    disable_caps_word();
    layer_off(_NAV);
    layer_off(_WNAV);
    layer_off(_SYM);
    layer_move(_BASE);
}

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(SE_A, KC_LEFT_ALT)
        SMTD_MT(SE_R, KC_LEFT_GUI)
        SMTD_MT(SE_S, KC_LEFT_CTRL)
        SMTD_MT(SE_T, KC_LSFT)

        SMTD_MT(SE_O, KC_LEFT_ALT)
        SMTD_MT(SE_I, KC_RIGHT_GUI)
        SMTD_MT(SE_E, KC_RIGHT_CTRL)
        SMTD_MT(SE_N, KC_RSFT)

        SMTD_LT_ON_MKEY(L_THMB_L, KC_ESC, _NAV) // placeholder layer
        SMTD_LT_ON_MKEY(L_THMB_M, KC_SPC, _NAV)
        SMTD_LT_ON_MKEY(L_THMB_R, KC_TAB, _SYM)

        SMTD_LT_ON_MKEY(R_THMB_L, KC_BSPC, _SYM) // placeholder layer
        SMTD_LT_ON_MKEY(R_THMB_M, KC_ENT, _SYM)
            //      SMTD_LT_ON_MKEY(R_THMB_R, KC_DEL, _SYM) // placeholder layer

        case R_THMB_R:
            uprintf("thmb");

            if (action == SMTD_ACTION_TAP) {
                uprintf("tap");

                if (is_leading()) {
                    stop_leading();
                } else {
                    uprintf("thmb");

                    start_leading();
                }
            } else if (action == SMTD_ACTION_HOLD) {
                layer_move(_SYM);
            } else if (action == SMTD_ACTION_RELEASE) {
                layer_off(_SYM);
                layer_move(_BASE);
            }
            return SMTD_RESOLUTION_DETERMINED;
    }

    return SMTD_RESOLUTION_UNHANDLED;
}
bool _process_record_user(uint16_t keycode, keyrecord_t *record) {
#if !defined(IS_ERGODOX) && !defined(IS_PLANCK)
#    error "This code is only for Ergodox or Planck keyboards"
#endif

    // Debugging

    if (!process_smtd(keycode, record)) {
        return false;
    }
    return true;
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
            clear();
            return false;
        case KC_ESC:
            clear();
            tap_escape();
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
                if (IS_LAYER_ON(_SYM)) {
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
// process_oneshot_pre(keycode, record);
#ifdef CONSOLE_ENABLE

    if (record->event.pressed) {
        keypos_t     *key           = &(record->event.key);
        uint8_t const current_layer = get_highest_layer(layer_state);
        uint8_t const qmk_fn        = keymap_key_to_keycode(current_layer, *key);
        uint8_t const lookup_table  = keymaps[current_layer][key->row][key->col];
        uprintf("qmk_fn: %u, lookup_table: %u\n", qmk_fn, lookup_table);
    }
#endif
    // If `false` was returned, then we did something special and should register that manually.
    // Otherwise register keyrepeat here by default.
    bool res = _process_record_user(keycode, record);

    //  process_oneshot_post(keycode, record);

    if (record->event.pressed) {
        last_key_down = keycode;
    } else {
        last_key_up = keycode;
    }

    return res;
}
