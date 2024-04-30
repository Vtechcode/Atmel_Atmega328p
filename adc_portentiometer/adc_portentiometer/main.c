#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUD 9600 // Define baud rate
#define MYUBRR F_CPU/16/BAUD - 1 

void USART_init(unsigned int ubrr)
{
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8 data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(uint16_t data)
{
	char result[20];
    // Convert ADC value to ASCII string
    char buffer[20]; // Increase buffer size
    snprintf(buffer, sizeof(buffer), "%u volts\n", data);
	
    
    // Transmit each character of the buffer
    for (int i = 0; buffer[i] != '\0'; i++) {
       // Wait for empty transmit buffer
       while (!(UCSR0A & (1 << UDRE0)));
       // Put data into buffer, send the data
       UDR0 = buffer[i];
         
    }
	 
}

void ADC_init()
{
	// select the analog channel 
	ADMUX |= (1 << MUX0) | (0 << MUX1) | (0 << MUX2) | (0 << MUX3);
	// set the auto trigger source to free running
	ADCSRB |= (0 << ADTS0) | (0 << ADTS1) | (0 << ADTS2);
	// Enable the ADC, Prescaling to 8-bit, and auto trigger
    ADCSRA |= ((1<<ADEN) | (1<<ADATE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2)) ;   
	// set the voltage reference    
    ADMUX |= (0<<REFS1)|(1<<REFS0);                                                              
    
}

int ADC_read()
{
	
    int Ain, AinLow;
    // wait for conversion to complete
    while(!(ADCSRA & (1 << ADIF)));
    
    AinLow = ADCL;        /* Read lower byte*/
    Ain =  (ADCH<<8);     /* Read higher 2 bits and 
                                  Multiply with weight */
    Ain = Ain | AinLow;
    return Ain * 5/1023;                /* Return digital value*/
}

ISR(ADC_vect)
{
	// This ISR will be executed when ADC conversion is complete
}

int main(void)
{
    //Initialize USART
    USART_init(MYUBRR);
    // Initialize ADC
    ADC_init();
    // Start the first conversion
    ADCSRA |= (1 << ADSC);
	
    // Enable global interrupts
    ADCSRA |= (1 << ADIE);
	sei();

    while (1)
    {
        // Transmit ADC values
        USART_Transmit(ADC_read());
        _delay_ms(5000);
    }
    return 0;
}
