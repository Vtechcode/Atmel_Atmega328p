/*
 * toggle-led-button.c
 *
 * Created: 3/28/2024 3:26:38 PM
 * Author : Vick
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
   DDRB |= (1 << DDB1);
   DDRB &= ~(1 << DDB0);
	
    while (1) 
    {
		if(!(PINB &(1 << PINB0)))
		{
			PORTB ^= (1 << PINB1);
			_delay_ms(300);
		}
	}
}

