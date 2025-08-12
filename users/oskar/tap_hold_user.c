#include <tap_hold.h>

#include "utils.h"
#include "casemodes.h"

// Tap hold
bool tap_hold(uint16_t keycode) {
    switch (keycode) {
        case SE_DQUO:
        case SE_QUOT:
        case SE_LABK:
        case SE_RABK:
        case SE_PERC:
        case GRV:
        case AT_E:
        case QE:
            //        case SE_AT:
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
            //        case SE_1:
            //        case SE_2:
            //        case SE_3:
            //        case SE_4:
            //        case SE_5:
            //        case SE_6:
            //        case SE_7:
            //        case SE_8:
            //        case SE_9:
            //        case SE_0:
            //        case G(SE_0):
            //        case G(SE_1):
            //        case G(SE_2):
            //        case G(SE_3):
            //        case G(SE_4):
            //        case G(SE_5):
            //        case G(SE_6):
            //        case G(SE_7):
            //        case G(SE_8):
            //        case G(SE_9):
            //        case G(SE_K):
            //        case G(SE_J):
            //        case G(SE_W):
            //        case G(SE_E):
            //        case G(SE_R):
            //        case G(SE_C):
            //        case G(SE_P):
        case G(KC_SPC):
        case G(KC_ENT):
            //        case SE_A ... SE_Z:
            //        case SE_ARNG:
            //        case SE_ADIA:
            //        case SE_ODIA:
            //        case E_ACUT:
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
        case SPLIT:
        case SPLIT_VS:
        case KC_ENT:
            return true;
        default:
            return false;
    }
}

void tap_hold_send_tap(uint16_t keycode) {
    switch (keycode) {
        case GRV:
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
        case SPLIT:
            tap_code16(C(SE_W));
            tap_code(SE_S);
            return;
        case SPLIT_VS:
            tap_code16(C(SE_W));
            tap_code(SE_V);
            return;
        case AT_E:
            send_string("@e");
            return;
        case QE:
            send_string("qe");
            return;
        default:
            tap_code16(keycode);
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
        case E_ACUT:
            tap_code16(SE_ACUT);
            tap_code16(S(SE_E));
            return;
        case CLOSE_WIN:
            tap_code16(S(G(SE_C)));
            return;
        case SPLIT:
            tap_code16(C(SE_B));
            send_string("\"");
            return;
        case SPLIT_VS:
            tap_code16(C(SE_B));
            send_string("%");
            return;
        default:
            tap_code16(S(keycode));
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
            return 135;
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
            return 115;
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
            return 110;
        // Slow index
        // Non here at the moment
        // Index
        default:
            return 110;
    }
}

void matrix_scan_user(void) {
    tap_hold_matrix_scan();
}
