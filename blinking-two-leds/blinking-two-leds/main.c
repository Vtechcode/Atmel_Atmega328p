/*
 * blinking-two-leds.c
 *
 * Created: 3/25/2024 5:01:06 PM
 * Author : Vick
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1 < DDB1) | (1 << DDB2);
    /* Replace with your application code */
    while (1) 
    {
		PORTB |= (1 << PORTB1);
		PORTB &=~ (1 << PORTB2);
		_delay_ms(1000);
		
		PORTB &=~ (1<<PORTB1);
		PORTB |= (1 << PORTB2);
		_delay_ms(1000);
    }
}

