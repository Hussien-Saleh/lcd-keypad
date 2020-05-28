/*
  program to control 4x16 LCD Display with 4-bits data mode using 4x4 Keypad.
  Requirements:
• Connect the LCD Data Path to the lower 4-pins on PORTD.
• Connect the “RS” LCD pin to PB1.
• Connect the “R/W” LCD pin to PB2.
• Connect the “E” LCD pin to PB3.
• 4x4 Keypad is connected at PORTA.
• Display the pressed keypad button on the LCD Display.
*/

#include "lcd_driver.h"
#include "keypad_driver.h"

int main(void)
{
	unsigned char key;
	LCD_init();
	LCD_displayStringRowColumn(0,0,"WELCOME");
	LCD_displayStringRowColumn(1,0,"Keypad 4x4");
	LCD_displayStringRowColumn(2,0,"LCD");
	LCD_goToRowColumn(3,0);
    while(1)
    { 
		key = KeyPad_getPressedKey(); 
		if((key <= 9) && (key >= 0))
		{
			LCD_integerToString(key); 
		}
		else
		{
			LCD_displayCharacter(key); 
		}
		_delay_ms(500); 
    }
}
