#include "casemodes.h"
#include "leader.h"
#include "utils.h"
#include "status.h"

// https://github.com/andrewjrae/kyria-keymap#userspace-leader-sequences
// void *_func(uint16_t keycode) {}

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
            //        case KC_X:
            //            return _func;
        case KC_C:
            tap_caps_lock();
            return NULL;
        case KC_W:
            enable_caps_word();
            return NULL;
        case KC_N:
            layer_invert(_NAV);
            return NULL;
        case KC_S:
            layer_invert(_SYM);
            return NULL;
        default:
            return NULL;
    }
}
