#include "shift_digit.h"
#include "shift_clock.h"

void shift_clock_open(void)
{
    shift_digit_open((void*)&k_shift_digit_hwcfg);
}

void shift_clock_wait(uint8_t tidx, uint16_t ti)
{
    hal_timer_A0_start(tidx, HAL_TIMER_ONE_SHOT, shift_clock_event, (void*)EVENT_WAIT, ti);
    shift_clock_wait_event(EVENT_WAIT);
}

void shift_clock_brightness_set(uint8_t percent)
{
    shift_digit_brightness_set(percent);
}
