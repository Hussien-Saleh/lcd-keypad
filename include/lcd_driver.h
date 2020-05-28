#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include "macros.h"
#include "mcu.h"
#include <stdint.h>

/* LCD Bit modes  */
#define BIT_MODE 8

#if (BIT_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD Pins */
#define RS                   PD0
#define RW                   PD1
#define E                    PD2
#define LCD_CTRL_PORT        PORTD
#define LCD_CTRL_PORT_DIR    DDRD
#define LCD_DATA_PORT        PORTB
#define LCD_DATA_PORT_DIR    DDRB

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80 

void LCD_init(void);
void LCD_sendCommand(uint8_t command);
void LCD_goToRowColumn(uint8_t row, uint8_t column);
void LCD_integerToString(uint32_t data);
void LCD_displayCharacter(uint8_t data);
void LCD_displayStringRowColumn(uint8_t row,uint8_t column,const char *pStr);
void LCD_displayString(const char *pStr);
void LCD_clearScreen(void);


#endif 
