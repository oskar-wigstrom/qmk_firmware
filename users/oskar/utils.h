#pragma once
#include <stdint.h>

bool tap_undead_key(bool key_down, uint16_t code);

void double_tap(uint16_t keycode);

void double_tap_space(uint16_t keycode);

void swap_caps_esc(void);

void tap_caps_lock(void);

void clear(void);
