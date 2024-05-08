#include "main.h"
#include "twi.h"
#include "lcd.h"
#include <avr/io.h>

int main(void) {

	
	_delay_ms(50);
	LCD_Init();

	_delay_ms(1000);
	LCD_clear();
	LCD_setPosition(0,0);
	LCD_sendString("<< Victor >>");
	
	// sendByte(0xC0,0);
	LCD_setPosition(1,1);
	LCD_sendString(">> Waburi <<");
	// sendByte(0x90,0);
	LCD_setPosition(0,2);
	LCD_sendString("Soft that works!");
	LCD_setPosition(1,3);
	LCD_sendString("codecranch.com ");
	LCD_BackLight(1);
	
	
	while (1) {
		_delay_ms(5000);
		LCD_BackLight(1);
		_delay_ms(5000);
		LCD_BackLight(1);
	}

	return 0;
}