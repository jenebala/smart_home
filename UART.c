/*
 * CFile1.c
 *
 * Created: 2019. 04. 21. 20:15:06
 *  Author: Jenei Balazs
 */ 

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char RXstring[100];
volatile char topic[100];
volatile char state[100];

uint8_t str=0;

uint8_t available=0;

uint8_t sep=0;
uint8_t	toptmp=0;
uint8_t statmp=0;

uint8_t RXREAD=0;



void USART_init(void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (3<<UCSZ00);
	
	UBRR1H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR1L = (uint8_t)(BAUD_PRESCALLER);
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	UCSR1C = (3<<UCSZ10);
}

unsigned char USART0_receive(void)
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART0_send(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void USART0_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00){
		USART0_send(*StringPtr);
	StringPtr++;}
}



unsigned char USART1_receive(void)
{
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

void USART1_send( unsigned char data)
{
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data;
}

void USART1_putstring(char* StringPtr)
{
	while(*StringPtr != 0x00){
		USART1_send(*StringPtr);
	StringPtr++;}
}

unsigned char MQTT_command_read()
{
RXstring[str]=USART0_receive();
available++;

if (RXstring[str]=='\n')
	{
		for(sep=0,str=0,toptmp=0,statmp=0;str<(available-1);)
		{
			if (RXstring[str]=='/')  {sep=1; str++;}
			if (RXstring[str]==':')  {sep=2; str++;}
			
			if (sep==1)
			{
				topic[toptmp++]=RXstring[str++];
				topic[toptmp]=0x00;
			}
			if (sep==2)
			{
				state[statmp++]=RXstring[str++];
				state[statmp]=0x00;
			}
			
			if(sep==0) str++;
		}
		
 		USART1_putstring(state);
		USART1_putstring("\n\r");
 		USART1_putstring(topic);
		USART1_putstring("\n\r");
		
		available=0;
		str=0;
		RXREAD=1;
		return RXREAD;
		
		
	}
	else str++;

}