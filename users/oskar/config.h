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

// Home-row mods: https://precondition.github.io/home-row-mods#tap-hold-configuration-settings
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200
#define SMTD_GLOBAL_TAP_TERM TAPPING_TERM
#define SMTD_GLOBAL_FOLLOWING_TAP_TERM TAPPING_TERM
#define SMTD_GLOBAL_SEQUENCE_TERM TAPPING_TERM / 2
#define SMTD_GLOBAL_RELEASE_TERM TAPPING_TERM / 4

// Prevent normal rollover on alphas from accidentally triggering mods.
// Now the default behavior!
// #define IGNORE_MOD_TAP_INTERRUPT
// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD
// Immediately turn on layer if key is pressed quickly
#define HOLD_ON_OTHER_KEY_PRESS

// Not supported without flto
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// Save space
// #define LAYER_STATE_8BIT
#define LAYER_STATE_16BIT

#define CAPS_WORD_IDLE_TIMEOUT 0
#define CAPS_WORD_TOGGLE_KEY
