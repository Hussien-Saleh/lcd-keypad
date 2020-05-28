#include "lcd_driver.h"

void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);
	
	#if (BIT_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0xF0; 
		#else
			LCD_DATA_PORT_DIR |= 0x0F; 
		#endif		 
		LCD_sendCommand(FOUR_BITS_DATA_MODE); 
		LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE); 
	#elif (BIT_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; 
		LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
	#endif
	
	LCD_sendCommand(CURSOR_OFF); 
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); 
	CLEAR_BIT(LCD_CTRL_PORT,RW); 
	_delay_ms(1); // wait for processing Tas = 50ns 
	SET_BIT(LCD_CTRL_PORT,E); 
	_delay_ms(1); // wait for processing Tpw-Tdws=190ns 

	#if (BIT_MODE == 4)
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (command & 0xF0);
		#else 
			LCD_DATA_PORT = ((command >> 4) & 0x0F);
		#endif

		_delay_ms(1); 
		CLEAR_BIT(LCD_CTRL_PORT,E); 
		_delay_ms(1); 
		SET_BIT(LCD_CTRL_PORT,E); 
		_delay_ms(1); 

		/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (command << 4) & 0xF0;
		#else 
			LCD_DATA_PORT = (command & 0x0F);
		#endif
		
		_delay_ms(1); 
		CLEAR_BIT(LCD_CTRL_PORT, E); 
		_delay_ms(1); 

	#elif (BIT_MODE == 8)
	    /* out the required command to the data bus D0 --> D7 */ 
		LCD_DATA_PORT = command; 
		_delay_ms(1); 
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#endif	
}



void LCD_goToRowColumn(uint8_t row , uint8_t column)
{
	uint8_t address;
	
	switch(row)
	{
		case 0:
				address = column;
				break;
		case 1:
				address = column + 0x40; 
				break;
		case 2:
				address = column + 0x10; 
				break;
		case 3:
				address = column + 0x50; 
				break;
	}					
	LCD_sendCommand(address | SET_CURSOR_LOCATION); 
	// to write to a specific address in the LCD, the following command (0b10000000 + address) is used 
}


void LCD_integerToString(uint32_t data)
{
   char buff[16]; /* String to hold Ascii value */
   itoa(data,buff,10); // convert integer to string of base 10 (decimal) */
   LCD_displayString(buff);
}

void LCD_displayCharacter(uint8_t data)
{
	SET_BIT(LCD_CTRL_PORT,RS); 
	CLEAR_BIT(LCD_CTRL_PORT,RW); 
	_delay_ms(1); // delay for processing Tas = 50ns 
	SET_BIT(LCD_CTRL_PORT,E); 
	_delay_ms(1); // delay for processing Tpw - Tdws = 190ns 

	#if (BIT_MODE == 4)
	
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (data & 0xF0);
		#else 
			LCD_DATA_PORT = ((data >> 4) & 0x0F);
		#endif

		_delay_ms(1); /* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
		_delay_ms(1); /* delay for processing Th = 13ns */
		SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
		_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

		/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (data << 4) & 0xF0;
		#else 
			LCD_DATA_PORT = (data & 0x0F);
		#endif
		
		_delay_ms(1); /* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
		_delay_ms(1); /* delay for processing Th = 13ns */

	#elif (BIT_MODE == 8)
		LCD_DATA_PORT = data; /* out the required data to the data bus D0 --> D7 */
		_delay_ms(1); /* delay for processing Tdsw = 100ns */
		CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
		_delay_ms(1); /* delay for processing Th = 13ns */
	#endif	
}

void LCD_displayStringRowColumn(uint8_t row,uint8_t column,const char *pStr)
{
	LCD_goToRowColumn(row,column); /* go to to the required LCD position */
	LCD_displayString(pStr); 
}

void LCD_displayString(const char *pStr)
{
	while((*pStr) != '\0')
	{
		LCD_displayCharacter(*pStr);
		pStr++;
	}	
	
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); 
}
