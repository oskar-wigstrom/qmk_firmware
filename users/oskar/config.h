/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_DISABLE_KEYCODES
#    define RGBLIGHT_LAYERS
#endif

// ----- Tap/hold timing -----
#define TAPPING_TERM 200   // base tap/hold threshold in ms
#define QUICK_TAP_TERM 120 // fast release always = tap
#define TAPPING_TERM_PER_KEY
#define FLOW_TAP_TERM 150

// ----- Resolution rules -----
// #define PERMISSIVE_HOLD         // pressing another key = hold
// #define TAPPING_FORCE_HOLD // prefer hold when interrupted
// #define HOLD_ON_OTHER_KEY_PRESS // force hold if another key is pressed

// ----- Home-row-specific helpers -----
#define CHORDAL_HOLD // multiple home row mods held together = holds
#define PERMISSIVE_HOLD

// Not supported without flto
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// Save space
// #define LAYER_STATE_8BIT
#define LAYER_STATE_16BIT

#define CAPS_WORD_IDLE_TIMEOUT 0
#define CAPS_WORD_TOGGLE_KEY

#define COMBO_ONLY_FROM_LAYER 0
