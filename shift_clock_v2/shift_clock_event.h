#ifndef _SHIFT_CLOCK_EVENTS_H_
#define _SHIFT_CLOCK_EVENTS_H_

#include "kal_event.h"

enum {
    EVENT_MINUTE_INCREMENT,
    EVENT_HOUR_INCREMENT,
    EVENT_DAY_INCREMENT,
    EVENT_BUTTON1_PUSH,
    EVENT_BUTTON2_PUSH,
    EVENT_BUTTON1_RELEASE,
    EVENT_BUTTON2_RELEASE,
    EVENT_BUTTON1_LONG_PRESS,
    EVENT_BUTTON2_LONG_PRESS,
    EVENT_BLINK_ON,
    EVENT_BLINK_OFF,
    EVENT_WAIT,
    EVENT_TRIGGER,
    EVENT_LIGHT_MEASURE,
    EVENT_QUANTITY,
    EVENT_ALL = KAL_EVENT_ALL,
};

void shift_clock_event_button(void* param);
void shift_clock_event_blink(void* param);
uint8_t shift_clock_wait_event(uint8_t event);
void shift_clock_set_event(uint8_t event);
void shift_clock_event(void* event);

#endif // _SHIFT_CLOCK_EVENTS_H_
