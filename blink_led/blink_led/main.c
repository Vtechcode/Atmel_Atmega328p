/*
 * blink_led.c
 *
 * Created: 4/15/2024 2:25:17 PM
 * Author : Vick
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL


int main(void)
{
DDRB |= (1 << DDB1);

    /* Replace with your application code */
    while (1) 
    {
		
		
			PORTB |= (1 << PORTB1);
			_delay_ms(1000);
			PORTB &=~ (1 << PORTB1);
			_delay_ms(1000);
		
		
    }
}

