#include "quantum.h"

#include "keycodes.h"
#include "status.h"
#include "quantum/caps_word.h"

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#include "features/custom_shift_keys.h"

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //    if (!process_smtd(keycode, record)) return false;

    if (!process_custom_shift_keys(keycode, record)) return false;

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
