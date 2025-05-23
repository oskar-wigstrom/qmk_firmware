/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "ergodox_ez.h"

/*
 * This constant define not debouncing time in msecs, assuming eager_pr.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * However, some switches seem to have higher debouncing requirements, or
 * something else might be wrong. (Also, the scan speed has improved since
 * that comment was written.)
 */

/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values

static matrix_row_t read_cols(uint8_t row);
static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;

void matrix_init_custom(void) {
    // initialize row and col

    mcp23018_status = init_mcp23018();

    unselect_rows();
    init_cols();
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
    matrix_row_t temp = 0x3F & read_cols(index);
    if (raw_matrix[index] != temp) {
        raw_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23018_status) { // if there was an error
        if (++mcp23018_reset_loop == 0) {
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
                ergodox_blink_all_leds();
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_init(); // re-init driver on reconnect
#endif
            }
        }
    }

#ifdef LEFT_LEDS
    mcp23018_status = ergodox_left_leds_update();
#endif // LEFT_LEDS
    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
        // select rows from left and right hands
        uint8_t left_index  = i;
        uint8_t right_index = i + MATRIX_ROWS_PER_SIDE;
        select_row(left_index);
        select_row(right_index);

        changed |= store_raw_matrix_row(left_index);
        changed |= store_raw_matrix_row(right_index);

        unselect_rows();
    }

    return changed;
}

/* Column pin configuration
 *
 * Teensy
 * col: 0   1   2   3   4   5
 * pin: F0  F1  F4  F5  F6  F7
 *
 * MCP23018
 * col: 0   1   2   3   4   5
 * pin: B5  B4  B3  B2  B1  B0
 */
static void init_cols(void) {
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    // init on teensy
    gpio_set_pin_input_high(F0);
    gpio_set_pin_input_high(F1);
    gpio_set_pin_input_high(F4);
    gpio_set_pin_input_high(F5);
    gpio_set_pin_input_high(F6);
    gpio_set_pin_input_high(F7);
}

static matrix_row_t read_cols(uint8_t row) {
    if (row < 7) {
        if (mcp23018_status) { // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            // reading GPIOB (column port) since in mcp23018's sequential mode
            // it is addressed directly after writing to GPIOA in select_row()
            mcp23018_status = i2c_receive(I2C_ADDR, &data, 1, ERGODOX_EZ_I2C_TIMEOUT);
            return ~data;
        }
    } else {
        /* read from teensy
         * bitmask is 0b11110011, but we want those all
         * in the lower six bits.
         * we'll return 1s for the top two, but that's harmless.
         */

        return ~((PINF & 0x03) | ((PINF & 0xF0) >> 2));
    }
}

/* Row pin configuration
 *
 * Teensy
 * row: 7   8   9   10  11  12  13
 * pin: B0  B1  B2  B3  D2  D3  C6
 *
 * MCP23018
 * row: 0   1   2   3   4   5   6
 * pin: A0  A1  A2  A3  A4  A5  A6
 */
static void unselect_rows(void) {
    // no need to unselect on mcp23018, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    // unselect on teensy
    gpio_set_pin_input(B0);
    gpio_set_pin_input(B1);
    gpio_set_pin_input(B2);
    gpio_set_pin_input(B3);
    gpio_set_pin_input(D2);
    gpio_set_pin_input(D3);
    gpio_set_pin_input(C6);
}

static void select_row(uint8_t row) {
    if (row < 7) {
        // select on mcp23018
        if (!mcp23018_status) {
            // set active row low  : 0
            // set other rows hi-Z : 1
            uint8_t data;
            data            = 0xFF & ~(1 << row);
            mcp23018_status = i2c_write_register(I2C_ADDR, GPIOA, &data, 1, ERGODOX_EZ_I2C_TIMEOUT);
        }
    } else {
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 7:
                gpio_set_pin_output(B0);
                gpio_write_pin_low(B0);
                break;
            case 8:
                gpio_set_pin_output(B1);
                gpio_write_pin_low(B1);
                break;
            case 9:
                gpio_set_pin_output(B2);
                gpio_write_pin_low(B2);
                break;
            case 10:
                gpio_set_pin_output(B3);
                gpio_write_pin_low(B3);
                break;
            case 11:
                gpio_set_pin_output(D2);
                gpio_write_pin_low(D2);
                break;
            case 12:
                gpio_set_pin_output(D3);
                gpio_write_pin_low(D3);
                break;
            case 13:
                gpio_set_pin_output(C6);
                gpio_write_pin_low(C6);
                break;
        }
    }
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    mcp23018_status = init_mcp23018();

    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}
