#ifndef _SHIFT_REGISTER_74HC595X_H_
#define _SHIFT_REGISTER_74HC595X_H_

#include "hal_gpio.h"

typedef struct {
    gpio_t io_ena;
    gpio_t io_sck;
    gpio_t io_ser;
    gpio_t io_rck;
    gpio_t io_clr;
} shift_register_74hc595x_hwcfg_t;

#endif // _SHIFT_REGISTER_74HC595X_H_
