#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define BRC F_CPU/16/BAUD - 1

void USART_init(unsigned int smt)
{
	//set the baud rate
	UBRR0H = (unsigned char)(smt >> 8);
	UBRR0L = (unsigned char)(smt);
	
	// activate Rx and Tx
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}



void USART_Transmit(unsigned char data)
{
	//Wait for transmit buffer to be empty
	while(!(UCSR0A & (1<<UDRE0)));

	UDR0 = data;
	
	
	//put data into buffer and transmit
	
}

unsigned char USART_Receive(void)
{
	
	//wait for data to be received
	while(!(UCSR0A & (1<<RXC0)));
	//return received data
	return UDR0;
}

void USART_led()
{

	
	PORTB |= (1 << PORTB1);
	USART_Transmit('N');
	
	
	
}
void USART_led_off()
{
	
	PORTB &=~ (1 << PORTB1);
	//USART_Transmit('F');
}



int main(void)
{

	DDRB |= (1 << DDB1);
	USART_init(BRC);
	while(1)
	{
		char received_char = USART_Receive();
		//USART_Transmit(received_char);
		if(received_char == 's')
		{
			USART_led();
			_delay_ms(1000);
		}
		else
		{
			USART_led_off();
		}
	}
	return 0;
}