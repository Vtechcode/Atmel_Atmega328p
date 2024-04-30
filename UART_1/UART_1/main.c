#include <avr/io.h>
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
	//put data into buffer and transmit
	UDR0 = data;
}

unsigned char USART_Receive(void)
{
	//wait for data to be received
	while(!(UCSR0A & (1<<RXC0)));
	//return received data
	return UDR0;
}

int main(void)
{

	USART_init(BRC);
	while(1)
	{
		USART_Transmit(USART_Receive());
	}
	return 0;
}