#pragma once

#include QMK_KEYBOARD_H

void set_led(uint8_t id, bool on);
bool is_caps_swapped(void);
bool in_linux(void);
