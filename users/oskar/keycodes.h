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

    // Instant leader key
    LEADER,

    // Repeat keys
    REPEAT,
    REV_REP,

    //
    AT_E,
    QE
};

#define xxxxxxx KC_NO

#define TG_NAV TG(_NAV)
#define TO_BASE TO(_BASE)

#define L_THMB_L LT(_NAV, KC_SPC)
#define L_THMB_R KC_TAB
#define R_THMB_L OS_SHFT
#define R_THMB_R KC_ENT

#define MY_RALT OSM(MOD_RALT)

#define ESC_SYM LT(_SYM, KC_ESC)
#define COLN_SYM LT(_SYM, SE_COLN)

#define TAB_MOD LT(_MODS, KC_TAB)

#define MY_LALT OSM(MOD_LALT)

#define NUM OSL(_NUM)
#define OS_WNAV OSL(_WNAV)
#define OPT OSL(_OPT)
#define SPEC OSL(_SPEC)
#define FUN OSL(_FUN)

#define SYM_LDQ ALGR(SE_V)    // “ v
#define SYM_RDQ ALGR(SE_B)    // ” b
#define SYM_LQO ALGR(S(SE_V)) // ‘ V
#define SYM_RQO ALGR(S(SE_B)) // ’ B
