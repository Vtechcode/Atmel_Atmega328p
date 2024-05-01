/*
 * twi_lcd.c
 *
 * Created: 5/1/2024 12:58:49 PM
 * Author : Vick
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#define BAUD 9600 //Define baud rate
#define SCL_FRQ F_CPU/(BAUD + 1)

void TWI_init_master(void) // function to initialize master
{
	TWBR = 0X01; // bitrate
	TWSR = (0 << TWPS1) | (0 << TWPS0); // setting prescalar bits
}

void TWI_start(void) // send start condition
{
	// Clear TWI interrupt flag, put start condition on SDA, Enable TWI
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT))); // Wait till start condition is transmitted
	while((TWSR & 0XF8) != 0X08); //check for the acknowledgement
}

void TWI_read_address(unsigned char data)// send the slave address data direction bit  and wait for the ACK signal
{
	TWDR = data; //Address and read instruction
	TWCR = (1 << TWINT) | (1 << TWEN); // clear TWI interrupt flag, Enable TWI
	while(!(TWCR & (1 << TWINT))); // Wait till complete TWDR byte received
	while((TWSR & 0XF8) != 0X40); //check for the acknowledgement
}

void TWI_write_data(unsigned char data) // send the 8 bit data and wait for the ACK
{
	TWDR = data; // put data in TWDR
	TWCR = (1 << TWINT) | (1 << TWEN); //clear TWI interrupt flag, Enable TWI
	while(!(TWCR & (1 << TWINT))); // Wait till TWDR byte is transmitted
	while((TWDR & 0XF8) != 0X28); //check for the acknowledgement
}

void TWI_stop(void) //send the STOP condition
{
	//Clear TWI interrupt flag, put stop condition on SDA, Enable Enable TWI
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while(!(TWCR & (1 << TWSTO))); // wait till stop condition is transmitted
}




int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

