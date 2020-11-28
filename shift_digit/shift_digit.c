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
    shift_register_enable();

    // Brightness control
    hal_pwm_A1_open(g_hwcfg->io_pwm);
    shift_digit_brightness_set(100);
    hal_pwm_A1_start();
}

void shift_digit_update(void)
{
    shift_register_update();
}

uint8_t shift_digit_char2byte(char c, bool dot)
{
    switch (c)
    {
        case '0': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case '1': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c |                                                                     ((dot)? g_hwcfg->seg_h : 0));
        case '2': return (g_hwcfg->seg_a | g_hwcfg->seg_b |                  g_hwcfg->seg_d | g_hwcfg->seg_e |                  g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '3': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d |                                   g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '4': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c |                                   g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '5': return (g_hwcfg->seg_a |                  g_hwcfg->seg_c | g_hwcfg->seg_d |                  g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '6': return (g_hwcfg->seg_a |                  g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '7': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c |                                                                     ((dot)? g_hwcfg->seg_h : 0));
        case '8': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '9': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d |                  g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '-': return (                                                                                                      g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case '_': return (                                                   g_hwcfg->seg_d |                                                    ((dot)? g_hwcfg->seg_h : 0));
        case ' ': return (                                                                                                                       ((dot)? g_hwcfg->seg_h : 0));
        case '.': return (                                                                                                                               g_hwcfg->seg_h);
        case 'A': // Fallthrough
        case 'a': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c |                  g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'B': // Fallthrough
        case 'b': return (                                  g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'C': // Fallthrough
        case 'c': return (g_hwcfg->seg_a |                                   g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case 'D': // Fallthrough
        case 'd': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e |                  g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'E': // Fallthrough
        case 'e': return (g_hwcfg->seg_a |                                   g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'F': // Fallthrough
        case 'f': return (g_hwcfg->seg_a |                                                    g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'G': // Fallthrough
        case 'g': return (g_hwcfg->seg_a |                  g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case 'H': // Fallthrough
        case 'h': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c |                  g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'I': // Fallthrough
        case 'i': return (                                                                    g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case 'J': // Fallthrough
        case 'j': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e |                                   ((dot)? g_hwcfg->seg_h : 0));
        //case 'K': // Fallthrough
        //case 'k': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'L': // Fallthrough
        case 'l': return (                                                   g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case 'M': // Fallthrough
        case 'm': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c |                  g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case 'N': // Fallthrough
        case 'n': return (                                  g_hwcfg->seg_c |                  g_hwcfg->seg_e |                  g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'O': // Fallthrough
        case 'o': return (                                  g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e |                  g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'P': // Fallthrough
        case 'p': return (g_hwcfg->seg_a | g_hwcfg->seg_b |                                   g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'Q': // Fallthrough
        case 'q': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c |                                   g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'R': // Fallthrough
        case 'r': return (                                                                    g_hwcfg->seg_e |                  g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'S': // Fallthrough
        case 's': return (                                  g_hwcfg->seg_c | g_hwcfg->seg_d |                  g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'T': // Fallthrough
        case 't': return (                                                   g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'U': // Fallthrough
        case 'u': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        case 'V': // Fallthrough
        case 'v': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f |                  ((dot)? g_hwcfg->seg_h : 0));
        //case 'W': // Fallthrough
        //case 'w': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'X': // Fallthrough
        case 'x': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c |                  g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        case 'Y': // Fallthrough
        case 'y': return (                 g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d |                  g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        //case 'Z': // Fallthrough
        //case 'z': return (g_hwcfg->seg_a | g_hwcfg->seg_b | g_hwcfg->seg_c | g_hwcfg->seg_d | g_hwcfg->seg_e | g_hwcfg->seg_f | g_hwcfg->seg_g | ((dot)? g_hwcfg->seg_h : 0));
        default: return (0x00);
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

// From 1 to 100
void shift_digit_brightness_set(uint8_t percent)
{
    if (percent < 1)
    {
        percent = 1;
    }
    else if (percent > 100)
    {
        percent = 100;
    }
    hal_pwm_A1_cfg(1024, 1024 - g_hwcfg->brightness_lut[percent-1]);
}
