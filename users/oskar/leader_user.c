#include "leader.h"
#include "utils.h"

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
        default:
            return NULL;
    }
}
