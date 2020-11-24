#include "shift_clock.h"

void shift_clock_print_time(date_t* date, bool dot)
{
    shift_digit_print_char((date->minute % 10) + '0', false);
    shift_digit_print_char((date->minute / 10) + '0', false);
    shift_digit_print_char((date->hour % 10) + '0', dot);
    shift_digit_print_char((date->hour / 10) + '0', false);
    shift_digit_update();
}

void shift_clock_print_blank(void)
{
    uint8_t i;

    for (i = SHIFT_CLOCK_SIZE; i > 0; i--)
    {
        shift_digit_print_char(' ', false);
    }
    shift_digit_update();
}

void shift_clock_print_full(void)
{
    uint8_t i;

    for (i = SHIFT_CLOCK_SIZE; i > 0; i--)
    {
        shift_digit_print_char('8', true);
    }
    shift_digit_update();
}
