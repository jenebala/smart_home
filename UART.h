/*
 * UART.h
 *
 * Created: 2019. 04. 21. 20:15:28
 *  Author: Jenei Balazs
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "define.h"


volatile char RXstring[100];
volatile char topic[100];
volatile char state[100];



#ifndef UART_H_
#define UART_H_

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART_init(void);
unsigned char USART0_receive(void);
void USART0_send( unsigned char data);
void USART0_putstring(char* StringPtr);
unsigned char USART1_receive(void);
void USART1_send( unsigned char data);
void USART1_putstring(char* StringPtr);
unsigned char MQTT_command_read();


#endif /* UART_H_ */