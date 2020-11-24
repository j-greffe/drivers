#ifndef _SHIFT_DIGIT_H_
#define _SHIFT_DIGIT_H_

// Digit segments:
//   ---a---
//  |       |
//  f       b
//  |       |
//   ---g---
//  |       |
//  e       c
//  |       |
//   ---d--- h

#include <stdint.h>
#include <stdbool.h>
#include "hal_gpio.h"

typedef struct {
    // Match segments to shift register output bits
    uint8_t seg_a;
    uint8_t seg_b;
    uint8_t seg_c;
    uint8_t seg_d;
    uint8_t seg_e;
    uint8_t seg_f;
    uint8_t seg_g;
    uint8_t seg_h;
    // Shift register hardware config
    void* shift_register_hwcfg;
    // PWM pin for brightness control
    gpio_t io_pwm;
    // int16_t[100] look up table to convert percent into PWM duty cycle (1-1023)
    const uint16_t* brightness_lut;
} shift_digit_hwcfg_t;

void shift_digit_open(void* hwcfg);
void shift_digit_update(void);
uint8_t shift_digit_char2byte(char c, bool dot);
void shift_digit_print_char(char c, bool dot);
void shift_digit_print_string(char* s);
void shift_digit_brightness_set(uint8_t percent);

#endif // _SHIFT_DIGIT_H_
