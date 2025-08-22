#include "quantum.h"

#include "keycodes.h"
#include "status.h"
#include "quantum/caps_word.h"

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#include "features/custom_shift_keys.h"
// #include "features/caps_word.h"
#include "features/sm_td.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

bool tap_undead_key(bool key_down, uint16_t code) {
    if (key_down) {
        tap_code16(code);
        tap_code16(KC_SPACE);
    }
    return false;
}
bool caps_word_press_user(uint16_t keycode) {
    uprintf("caps_word_press_user: %04X\n", keycode);
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case SE_1 ... SE_0:
        case SE_MINS:
        case SE_UNDS:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
// clang-format off
const custom_shift_key_t custom_shift_keys[] = {
    {SE_COMM, SE_SCLN},
    {SE_DOT, SE_COLN},
    {SE_QUOT, SE_ASTR},
    {SE_SLSH, SE_QUES},
    {SE_PLUS, SE_EQL},
    {KC_BSPC, KC_DEL},
    // nums
    {SE_2, SE_AT},
    {SE_4, SE_DLR},
    {SE_7, SE_CIRC},
    {SE_8, SE_DQUO},
    {SE_9, SE_COLN},
};
// clang-format on
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

bool my_lt(smtd_action action, uint16_t pressed, uint16_t keycode, uint16_t layer) {
    if (pressed != keycode) {
        return false;
    }
    switch (action) {
        case SMTD_ACTION_TOUCH:
            break;
        case SMTD_ACTION_TAP:
            caps_word_off();
            tap_code16(keycode);
            break;
        case SMTD_ACTION_HOLD:
            LAYER_PUSH(layer);
            break;
        case SMTD_ACTION_RELEASE:
            LAYER_RESTORE();
            break;
    }
    return true;
}
smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    if (my_lt(action, keycode, KC_SPC, _NAV) || my_lt(action, keycode, KC_ESC, _SNUM) || my_lt(action, keycode, KC_ENT, _SYM) || my_lt(action, keycode, KC_TAB, _NUM)) {
        return SMTD_RESOLUTION_DETERMINED;
    }
    switch (keycode) {
        SMTD_LT(KC_ENT, _SYM)
        SMTD_LT(KC_TAB, _SYM)

        SMTD_MT(SE_A, KC_LEFT_ALT)
        SMTD_MT(SE_R, KC_LEFT_GUI)
        SMTD_MT(SE_S, KC_LEFT_CTRL)
        SMTD_MT(SE_T, KC_LSFT)

        SMTD_MT(SE_O, KC_LEFT_ALT)
        SMTD_MT(SE_I, KC_RIGHT_GUI)
        SMTD_MT(SE_E, KC_RIGHT_CTRL)
        SMTD_MT(SE_N, KC_RSFT)
    }
    return SMTD_RESOLUTION_UNHANDLED;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uprintf("process_record_user: %04X %s\n", keycode, record->event.pressed ? "pressed" : "released");
    if (!process_smtd(keycode, record)) return false;
    uprintf("process_record_user: after smtd\n");
    if (!process_custom_shift_keys(keycode, record)) return false;
    // if (!process_caps_word(keycode, record)) return false;

    switch (keycode) {
        case TILD:
            return tap_undead_key(record->event.pressed, SE_TILD);
        case CIRC:
            return tap_undead_key(record->event.pressed, SE_CIRC);
        case TG_SWE:
            if (record->event.pressed) {
                layer_invert(_SWE);
            }
            return false;
        case CAPS_WORD:
            caps_word_on();
            uprintf("Caps Word activated\n");
            return false;
    }

    return true;
}
