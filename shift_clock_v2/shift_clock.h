#ifndef _SHIFT_CLOCK_H_
#define _SHIFT_CLOCK_H_

#include <stdint.h>
#include <string.h>

#include "main.h"
#include "hal_irq.h"
#include "hal_timer.h"
#include "hwcfg.h"

#define SHIFT_CLOCK_SIZE 4

#define BUTTON_LONG_PRESS_TIME 1536

// TimerA_0
enum {
    TIMER_COUNT,
    TIMER_BUTTON1,
    TIMER_BLINK,
};

typedef struct {
    uint8_t hour;
    uint8_t minute;
} date_t;

#include "shift_digit.h"
#include "shift_clock_event.h"
#include "shift_clock_input.h"
#include "shift_clock_print.h"

void shift_clock_open(void);
void shift_clock_wait(uint8_t tidx, uint16_t ti);
void shift_clock_brightness_set(uint8_t percent);

#endif // _SHIFT_DIGIT_H_
