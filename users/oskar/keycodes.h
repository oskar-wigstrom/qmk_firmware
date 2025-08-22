#pragma once

#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "quantum.h"
#include "quantum/action.h"
#include "quantum/quantum_keycodes.h"

enum layers { _BASE = 0, _SWE, _NAV, _SYM, _NUM, _SNUM };

enum custom_keycodes {
    // Direct dead keys ~`^
    TILD = QK_USER,
    GRV,
    CIRC,

    TG_SWE,

    LEADER,
    CAPS_WORD,
};

#define xxxxxxx KC_NO

#define COPY C(S(SE_C))
#define PASTE C(S(SE_V))
#define CUT C(S(SE_X))

#define UNDO C(SE_Z)
#define REDO C(S(SE_Z))
