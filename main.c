#include <avr/io.h>
#include <avr/interrupt.h>
#include "define.h"
#include <util/delay.h>
#include "UART.h"
#include "timer.h"
#include "io.h"


uint8_t RXREAD_OK=2;



int main(void)
{
	timerini();
	portini();
	USART_init();
	
    while (1) 
    {	
	
	}
}

ISR(TIMER1_COMPA_vect)
{	
	ledblink(3); // megszakitás futást jelzo led
	
	if (RXREAD_OK==1) // parancs beolvasása megtortént
	{
	cli();
	set_relay_mqtt(topic,state);
	sei();
	RXREAD_OK=2; // ujabb beolvasás engedélyezve
	}
	
	
	timer_setrelayfunc();
	
	
	//set_relay(INPF7,RelayPA0,TMPPF7,"setrelay/PF7");	
	//set_relay(INPF6,RelayPA1,TMPPF6,"setrelay/PF6");
	//set_relay(INPF5,RelayPA2,TMPPF5,"setrelay/PF5");
	
	set_relay(INPF4,RelayPA3,TMPPF4,"setrelay/PF4");
	set_relay(INPF3,RelayPA4,TMPPF3,"setrelay/PF3");
	set_relay(INPF2,RelayPA5,TMPPF2,"setrelay/PF2");
	set_relay(INPF1,RelayPA6,TMPPF1,"setrelay/PF1");
	set_relay(INPF0,RelayPA7,TMPPF0,"setrelay/PF0");

	set_relay(INPE0,RelayPC7,TMPPE0,"setrelay/PE0");
	set_relay(INPE1,RelayPC6,TMPPE1,"setrelay/PE1");
	set_relay(INPE2,RelayPC5,TMPPE2,"setrelay/PE2");
	set_relay(INPE3,RelayPC4,TMPPE3,"setrelay/PE3");
	set_relay(INPE4,RelayPC3,TMPPE4,"setrelay/PE4");
	set_relay(INPE5,RelayPC2,TMPPE5,"setrelay/PE5");
	set_relay(INPE6,RelayPC1,TMPPE6,"setrelay/PE6");
	set_relay(INPE7,RelayPC0,TMPPE7,"setrelay/PE7");
	
	set_relay(INPB7,RelayPD5,TMPPB7,"setrelay/PB7");
	set_relay(INPB6,RelayPD6,TMPPB6,"setrelay/PB6");
	set_relay(INPB5,RelayPD7,TMPPB5,"setrelay/PB5");
	
// 	set_mqtt(INPB4,TMPPB4,"setrelay/PB4");
// 	set_mqtt(INPB3,TMPPB3,"setrelay/PB3");
// 	set_mqtt(INPB2,TMPPB2,"setrelay/PB2");
// 	set_mqtt(INPB1,TMPPB1,"setrelay/PB1");
	set_mqtt(INPB0,TMPPB0,"setrelay/PB0");
	
}


ISR(USART0_RX_vect)
{	
	if (RXREAD_OK==2) // parancs beolvaás engedélyezve ?
	{
	RXREAD_OK=MQTT_command_read();
	}
}


ISR(USART1_RX_vect)
{
	
}