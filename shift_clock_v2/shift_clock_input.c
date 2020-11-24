#include "shift_clock.h"
#include "shift_digit.h"

static void shift_clock_input_print_hour_off(date_t* date)
{
    shift_digit_print_char((date->minute % 10) + '0', false);
    shift_digit_print_char((date->minute / 10) + '0', false);
    shift_digit_print_char(' ', true);
    shift_digit_print_char(' ', false);
    shift_digit_update();
}

static void shift_clock_input_print_minute_off(date_t* date)
{
    shift_digit_print_char(' ', false);
    shift_digit_print_char(' ', false);
    shift_digit_print_char((date->hour % 10) + '0', true);
    shift_digit_print_char((date->hour / 10) + '0', false);
    shift_digit_update();
}

void shift_clock_input_hour(date_t* date)
{
    uint8_t event;
    
    hal_timer_A0_start(TIMER_BLINK, HAL_TIMER_CONTINOUS, shift_clock_event_blink, 0, 300);
        
    shift_clock_print_time(date, true);
    
    do {
        event = shift_clock_wait_event(KAL_EVENT_ALL);
        
        if (EVENT_BUTTON1_RELEASE == event)
        {
            date->hour++;
            if (date->hour > 23) { date->hour = 0; }
            shift_clock_print_time(date, true);
        }
        else if (EVENT_BUTTON2_RELEASE == event)
        {
            if (date->hour <= 0) { date->hour = 24; }
            date->hour--;
            shift_clock_print_time(date, true);
        }
        else if (EVENT_BUTTON1_LONG_PRESS == event)
        {
            break;
        }
        else if (EVENT_BLINK_ON == event)
        {
            shift_clock_print_time(date, true);
        }
        else if (EVENT_BLINK_OFF == event)
        {
            shift_clock_input_print_hour_off(date);
        }
    } while (1);
    
    hal_timer_A0_stop(TIMER_BLINK);
}

void shift_clock_input_minute(date_t* date)
{
    uint8_t event;
    
    hal_timer_A0_start(TIMER_BLINK, HAL_TIMER_CONTINOUS, shift_clock_event_blink, 0, 300);
        
    shift_clock_print_time(date, true);
    
    do {
        event = shift_clock_wait_event(KAL_EVENT_ALL);
        
        if (EVENT_BUTTON1_RELEASE == event)
        {
            date->minute++;
            if (date->minute > 59) { date->minute = 0; }
            shift_clock_print_time(date, true);
        }
        else if (EVENT_BUTTON2_RELEASE == event)
        {
            if (date->minute <= 0) { date->minute = 60; }
            date->minute--;
            shift_clock_print_time(date, true);
        }
        else if (EVENT_BUTTON1_LONG_PRESS == event)
        {
            break;
        }
        else if (EVENT_BLINK_ON == event)
        {
            shift_clock_print_time(date, true);
        }
        else if (EVENT_BLINK_OFF == event)
        {
            shift_clock_input_print_minute_off(date);
        }
    } while (1);
    
    hal_timer_A0_stop(TIMER_BLINK);
}

void shift_clock_input_new_time(date_t* date)
{
    shift_clock_input_hour(date);
    shift_clock_input_minute(date);
}
