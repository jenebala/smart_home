#include <avr/io.h>
#include <avr/interrupt.h>
#include "define.h"
#include <util/delay.h>
#include "UART.h"
#include "timer.h"
#include "io.h"


uint8_t RXREAD_OK=0;



int main(void)
{
	timerini();
	portini();
	USART_init();
	
    while (1) 
    {	
		_delay_ms(100);
		if (RXREAD_OK==1)
		{
			cli();
			RXREAD_OK=0;			
			set_relay_mqtt(topic,state);
			sei();
		}	
	}
}

ISR(TIMER1_COMPA_vect)
{	
	ledblink(3); // megszakitás futást jelzo led
	
	
	timer_setrelayfunc();
	
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
}


ISR(USART0_RX_vect)
{	
	RXREAD_OK=MQTT_command_read();
}


ISR(USART1_RX_vect)
{
	
}