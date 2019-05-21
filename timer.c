/*
 * timer.c
 *
 * Created: 2019. 04. 21. 20:24:49
 *  Author: Jenei Balazs
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timerini() // timer megszakitás 100 ms enként, gomb polling
{
	TCCR1A = 0x80;
	TCCR1B = 0x0B;
	OCR1AH = 0x30;
	OCR1AL = 0xD3;
	TIMSK = 0b00010001;
	sei();
}