#pragma once

#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "quantum.h"
#include "quantum/action.h"
#include "quantum/quantum_keycodes.h"
#include "oneshot.h"

enum layers { _BASE = 0, _SWE, _NUM, _NAV, _WNAV, _SYM, _MODS, _FUN };

enum custom_keycodes {
    // Direct dead keys ~`^
    TILD = QK_USER,
    GRV,
    CIRC,

    // Vim
    SAVE_VIM,
    CLOSE_WIN,
    SPLIT_VS,
    SPLIT,

    // É
    E_ACUT,

    // Custom keycodes for instant processing for NUMWORD
    NUM_G,

    // Instant oneshot mods
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,

    // Smart caps lock and layers that turn off on certain keys
    CAPSWORD,
    NUMWORD,

    // Layer management
    CANCEL, // Cancel SYMWORD and NUMWORD
    CLEAR,  // Clear all WORD, one-shots and reset to BASE

    TG_SWE,

    // Repeat keys
    REPEAT,
    REV_REP,

    //
    AT_E,
    QE,

    // Homerow mods
    SMTD_KEYCODES_BEGIN,
    HR_A,
    HR_R,
    HR_S,
    HR_T,
    HR_N,
    HR_E,
    HR_I,
    HR_O,
    LEADER_SYM,
    SMTD_KEYCODES_END,
};

#define xxxxxxx KC_NO

#define L_THMB_L LT(_NAV, KC_SPC)
#define L_THMB_R LEADER_SYM
#define R_THMB_L LT(_NAV, KC_TAB)
#define R_THMB_R LT(_SYM, KC_ENT)

#define COLN_SYM LT(_SYM, SE_COLN)

#define NUM OSL(_NUM)
#define OS_WNAV OSL(_WNAV)
#define OPT OSL(_OPT)
#define SPEC OSL(_SPEC)
#define FUN OSL(_FUN)
