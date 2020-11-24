#include <string.h>
#include "hal_pwm.h"
#include "shift_register.h"
#include "shift_digit.h"
#include "hwcfg.h"

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

static shift_digit_hwcfg_t* g_hwcfg;

void shift_digit_open(void* hwcfg)
{
    g_hwcfg = (shift_digit_hwcfg_t*)hwcfg;

    shift_register_open(g_hwcfg->shift_register_hwcfg);

    // Brightness control
    shift_digit_brightness_set(100);
}

void shift_digit_update(void)
{
    shift_register_update();
}

uint8_t shift_digit_char2byte(char c, bool dot)
{    
    switch (c)
    {
        case '0': return g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f                  | (dot)? g_hwcfg->seg_h : 0;
        case '1': return                  g_hwcfg->seg_b | g_hwcfg->seg_c                                                                     | (dot)? g_hwcfg->seg_h : 0;
        case '2': return g_hwcfg->seg_a | g_hwcfg->seg_b |                  g_hwcfg->seg_d | g_hwcfg->seg_e |                  g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '3': return g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d |                                   g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '4': return                  g_hwcfg->seg_b | g_hwcfg->seg_c |                                   g_hwcfg->seg_f | g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '5': return g_hwcfg->seg_a |                  g_hwcfg->seg_c | g_hwcfg->seg_d |                  g_hwcfg->seg_f | g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '6': return g_hwcfg->seg_a |                  g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '7': return g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c                                                                     | (dot)? g_hwcfg->seg_h : 0;
        case '8': return g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '9': return g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d |                  g_hwcfg->seg_f | g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '-': return                                                                                                       g_hwcfg->seg_g | (dot)? g_hwcfg->seg_h : 0;
        case '_': return                                                    g_hwcfg->seg_d                                                    | (dot)? g_hwcfg->seg_h : 0;
        case ' ': return                                                                                                                        (dot)? g_hwcfg->seg_h : 0;
        case '.': return                                                                                                                               g_hwcfg->seg_h;
        default: return 0x00;
        // TODO: Letters
    }
}

void shift_digit_print_char(char c, bool dot)
{
    shift_register_push_byte(shift_digit_char2byte(c, dot));
}

void shift_digit_print_string(char* s)
{
    uint8_t i;
    uint8_t length = strlen(s);
    
    // Start with end of string.
    for (i = length; i > 0; i--)
    {
        shift_digit_print_char(s[i-1], false);
    }
}

void shift_digit_brightness_set(uint8_t percent)
{
    if (100 <= percent || 1024 <= g_hwcfg->brightness_lut[percent-1])
    {
        hal_pwm_A1_stop();
        // Enable is active low.
        hal_gpio_clr(g_hwcfg->io_pwm);
        hal_gpio_cfg(g_hwcfg->io_pwm, HAL_IO_OUT);
    }
//    else if (0 == percent)
//    {
//        hal_pwm_A1_stop();
//        // Enable is active low.
//        hal_gpio_set(g_hwcfg->io_pwm);
//        hal_gpio_cfg(g_hwcfg->io_pwm, HAL_IO_OUT);
//    }
    else
    {
        hal_pwm_A1_open(g_hwcfg->io_pwm);
        hal_pwm_A1_cfg(60, 1024 - g_hwcfg->brightness_lut[percent-1]);
        hal_pwm_A1_start();
    }
}
