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

#define L_TMB_L LT(_SNUM, KC_ESC)
#define L_TMB_M LT(_NAV, KC_SPC)
#define L_TMB_R LT(_NUM, KC_TAB)

#define R_TMB_M LT(_SYM, KC_ENT)

#define HR_A MT(MOD_LALT, SE_A)
#define HR_R MT(MOD_LGUI, SE_R)
#define HR_S MT(MOD_LCTL, SE_S)
#define HR_T MT(MOD_LSFT, SE_T)

#define HR_O MT(MOD_LALT, SE_O)
#define HR_I MT(MOD_RGUI, SE_I)
#define HR_E MT(MOD_RCTL, SE_E)
#define HR_N MT(MOD_RSFT, SE_N)
