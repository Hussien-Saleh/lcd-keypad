#ifndef _KEYPAD_DRIVER_H_
#define _KEYPAD_DRIVER_H_

#include "mcu.h"
#include "macros.h"
#include <stdint.h>

#define KEYPAD_PORTX      PORTA
#define KEYPAD_PINX       PINA
#define KEYPAD_DDRX       DDRA 
#define COLUMNS_NO         4
#define ROWS_NO            4

uint8_t KeyPad_getPressedKey(void);
#if (COLUMNS_NO == 4)
uint8_t KeyPad_4x4_adjustKeyNumber(uint8_t keyNumber);
#elif (COLUMNS_NO == 3)
uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t keyNumber);
#endif

#endif 
