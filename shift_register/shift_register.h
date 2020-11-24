#ifndef _SHIFT_REGISTER_H_
#define _SHIFT_REGISTER_H_

#include <stdint.h>
#include <stdbool.h>

void shift_register_open(void* hwcfg);
void shift_register_enable(void);
void shift_register_disable(void);
void shift_register_push_bit(bool bit);
void shift_register_push_byte(uint8_t byte);
void shift_register_update(void);
void shift_register_clear(void);

#endif // _SHIFT_REGISTER_H_
