#include "keypad_driver.h"

uint8_t KeyPad_getPressedKey(void){

	uint8_t column,row;
	for(;;)
	{
		for(column=0; column < COLUMNS_NO; ++column) 
		{
			/* 
			 * row pins are connected as bits  0-3 of PORTA
			 * column pins are connected as bits 4-7 of PORTA
			 * only 1 column pin is configured as Output LOW at each round 
			 * and all the other pins are configured as Input tristate (Hi-Z)
			 */ 

			KEYPAD_DDRX = (0x10<<column); 
			
			/* 
			 * clear the correponding column pin in PORTX to switch off pull-up resistor
			 * for this pin (TRI)
			 * enable the pull-up pin resistors for other columns and rows pins 
			 */ 

			KEYPAD_PORTX = (~(0x10<<column)); 

			for(row=0; row < ROWS_NO; ++row) 
			{
				/* check if a key is pressed in the current row
				 it means key is pressed when it is connected to low as the pull ups
				 keep their value high when they are floating (not pressed)
				 */
			
				if(BIT_IS_CLEAR(KEYPAD_PINX,row))
				{
					#if (COLUMNS_NO == 4)  
						return KeyPad_4x4_adjustKeyNumber((row * COLUMNS_NO) + column + 1); 
					#elif (COLUMNS_NO == 3)
						return KeyPad_4x3_adjustKeyNumber((row * COLUMNS_NO) + column + 1);
					#endif				
				}
			}
		}
	}	
}

#if (COLUMNS_NO == 4) 
uint8_t KeyPad_4x4_adjustKeyNumber(uint8_t keyNumber)
{
	switch(keyNumber)
	{
		case 1: return 7; 
				break;
		case 2: return 8; 
				break;
		case 3: return 9; 
				break;
		case 4: return '%'; // ASCII Code 
				break;
		case 5: return 4; 
				break;
		case 6: return 5;
				break;
		case 7: return 6; 
				break;
		case 8: return '*'; 
				break;		
		case 9: return 1; 
				break;
		case 10: return 2; 
				break;
		case 11: return 3; 
				break;
		case 12: return '-'; 
				break;
		case 13: return 13;  // ASCII of CR 
				break;			
		case 14: return 0; 
				break;
		case 15: return '='; 
				break;
		case 16: return '+'; 
				break;
		default: return keyNumber;								 						
	}
} 
#elif (COLUMNS_NO== 3) 

uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t keyNumber)
{
	switch(keyNumber)
	{
		case 10: return '*'; 
				 break;
		case 11: return 0;
				 break;		
		case 12: return '#';  
				 break;
		default: return keyNumber;								 						
	}
} 
#endif