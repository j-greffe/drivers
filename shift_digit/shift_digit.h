#ifndef _SHIFT_DIGIT_H_
#define _SHIFT_DIGIT_H_

#include <stdint.h>
#include <stdbool.h>
#include "hal_gpio.h"

typedef struct {
    uint8_t seg_a;
    uint8_t seg_b;
    uint8_t seg_c;
    uint8_t seg_d;
    uint8_t seg_e;
    uint8_t seg_f;
    uint8_t seg_g;
    uint8_t seg_h;
    void* shift_register_hwcfg;
    gpio_t io_ena; // Brightness PWM
    const uint16_t* brightness_lut; // LUT[100]: % to 1-1023 for PWM
} shift_digit_hwcfg_t;

void shift_digit_open(void* hwcfg);
void shift_digit_update(void);
void shift_digit_clear(void);
void shift_digit_enable(void);
void shift_digit_disable(void);
uint8_t shift_digit_char2byte(char c, bool dot);
uint8_t shift_digit_int2byte(int i, bool dot);
void shift_digit_print_char(char c, bool dot);
void shift_digit_print_string(char* s);
void shift_digit_brightness_set(uint8_t percent);

#endif // _SHIFT_DIGIT_H_
