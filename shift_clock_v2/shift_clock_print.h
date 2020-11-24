#ifndef _SHIFT_CLOCK_PRINT_H_
#define _SHIFT_CLOCK_PRINT_H_

#include <stdint.h>
#include <stdbool.h>
#include "shift_clock.h"

void shift_clock_print_time(date_t* date, bool dot);
void shift_clock_print_blank(void);
void shift_clock_print_full(void);

#endif // _SHIFT_CLOCK_PRINT_H_
