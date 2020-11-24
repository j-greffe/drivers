#include "shift_register.h"
#include "shift_register_74hc595x.h"

static shift_register_74hc595x_hwcfg_t* g_hwcfg;

void shift_register_open(void* hwcfg)
{
    g_hwcfg = (shift_register_74hc595x_hwcfg_t*)hwcfg;

    // All outputs
    hal_gpio_cfg(g_hwcfg->io_ena, HAL_IO_OUT);
    hal_gpio_cfg(g_hwcfg->io_sck, HAL_IO_OUT);
    hal_gpio_cfg(g_hwcfg->io_ser, HAL_IO_OUT);
    hal_gpio_cfg(g_hwcfg->io_rck, HAL_IO_OUT);
    hal_gpio_cfg(g_hwcfg->io_clr, HAL_IO_OUT);

    // Initial state disabled
    hal_gpio_set(g_hwcfg->io_ena);
    hal_gpio_clr(g_hwcfg->io_sck);
    hal_gpio_clr(g_hwcfg->io_ser);
    hal_gpio_clr(g_hwcfg->io_rck);
    hal_gpio_set(g_hwcfg->io_clr);
}

void shift_register_enable(void)
{
    // Enable is active low.
    hal_gpio_clr(g_hwcfg->io_ena);
}

void shift_register_disable(void)
{
    // Enable is active low.
    hal_gpio_set(g_hwcfg->io_ena);
}

void shift_register_push_bit(bool bit)
{
    // Set data pin
    if (bit)
    {
        hal_gpio_set(g_hwcfg->io_ser);
    }
    else
    {
        hal_gpio_clr(g_hwcfg->io_ser);
    }
    
    // Pulse clock pin. Data is pushed on rising edge.
    hal_gpio_set(g_hwcfg->io_sck);
    hal_gpio_clr(g_hwcfg->io_sck);
}
 
void shift_register_push_byte(uint8_t byte)
{
    uint8_t i;

    for (i = 8; i > 0; i--)
    {
         // MSB first!
         shift_register_push_bit(!!(byte & (1 << (i - 1))));
    }
}

void shift_register_update(void)
{
    // Pulse latch pin. Latch on rising edge.
    hal_gpio_set(g_hwcfg->io_rck);
    hal_gpio_clr(g_hwcfg->io_rck);
}

void shift_register_clear(void)
{
    // Pulse clear pin. Clear is active low.
    hal_gpio_clr(g_hwcfg->io_clr);
    hal_gpio_set(g_hwcfg->io_clr);
}
