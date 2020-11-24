#include "shift_clock.h"
#include "shift_clock_event.h"

void shift_clock_event_button(void* param)
{
    switch ((int)param)
    {
    case EVENT_BUTTON1_PUSH:
        hal_timer_A0_start(TIMER_BUTTON1, HAL_TIMER_ONE_SHOT, shift_clock_event_button, (void*)EVENT_BUTTON1_LONG_PRESS, BUTTON_LONG_PRESS_TIME);
        hal_irq_set(IO_BUTTON1, HAL_IRQ_RISING, shift_clock_event_button, (void*)EVENT_BUTTON1_RELEASE);
        hal_irq_en(IO_BUTTON1);
        shift_clock_set_event(EVENT_BUTTON1_PUSH);
        break;
    case EVENT_BUTTON1_RELEASE:
        hal_timer_A0_stop(TIMER_BUTTON1);
        hal_irq_set(IO_BUTTON1, HAL_IRQ_FALLING, shift_clock_event_button, (void*)EVENT_BUTTON1_PUSH);
        hal_irq_en(IO_BUTTON1);
        shift_clock_set_event(EVENT_BUTTON1_RELEASE);
        break;
    case EVENT_BUTTON2_PUSH:
        hal_irq_set(IO_BUTTON2, HAL_IRQ_RISING, shift_clock_event_button, (void*)EVENT_BUTTON2_RELEASE);
        hal_irq_en(IO_BUTTON2);
        shift_clock_set_event(EVENT_BUTTON2_PUSH);
        break;
    case EVENT_BUTTON2_RELEASE:
        hal_irq_set(IO_BUTTON2, HAL_IRQ_FALLING, shift_clock_event_button, (void*)EVENT_BUTTON2_PUSH);
        hal_irq_en(IO_BUTTON2);
        shift_clock_set_event(EVENT_BUTTON2_RELEASE);
        break;
    case EVENT_BUTTON1_LONG_PRESS:
        shift_clock_event(param);
    default:
        break;
    }
}

void shift_clock_event_blink(void* param)
{
    static bool on;
    
    if (on)
    {
        shift_clock_set_event(EVENT_BLINK_ON);
    }
    else
    {
        shift_clock_set_event(EVENT_BLINK_OFF);
    }
    
    on = !on;
}

uint8_t shift_clock_wait_event(uint8_t event)
{
    uint8_t new_event;
    static bool ignore_next_button_release;
    
    do {
        new_event = kal_event_wait(event);
    
        // Ignore button release after a long press
        if (EVENT_BUTTON1_RELEASE == new_event && ignore_next_button_release)
        {
            ignore_next_button_release = false;
            continue;
        }

        if (EVENT_BUTTON1_LONG_PRESS == new_event)
        {
            ignore_next_button_release = true;
        }

        break;
    } while (1);
    
    return new_event;
}

void shift_clock_set_event(uint8_t event)
{
    kal_event_set(event);
}

void shift_clock_event(void* event)
{
    kal_event_set((uint8_t)event);
}
