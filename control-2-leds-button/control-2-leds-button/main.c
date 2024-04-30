/*
 * control-2-leds-button.c
 *
 * Created: 3/26/2024 3:20:14 PM
 * Author : Vick
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRB |= (1 << DDB1);
	DDRB &=~ (1 << DDB0);
    while (1) 
    {
		if((PINB & (1 << PINB0)))
		
		
		{
			PORTB |= (1 << PINB1) ;
		}
		else
		{
			PORTB &= ~(1 << PINB1) ;
		}
    }
}

