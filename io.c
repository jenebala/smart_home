#include <avr/io.h>
#include "define.h"
#include <string.h>

uint32_t relayout=0;
uint8_t tmpled=0;

uint16_t PF7tim=0;
uint8_t PF7gny=0;
uint8_t PF7startidozito=0;
uint8_t PF7timer=0;
uint8_t PF7lampa=0;

uint8_t PF6gny=0;
uint8_t PF6lampa=0;

uint8_t PF5gny=0;
uint8_t PF5lampa=0;

volatile uint32_t gny=0;
volatile uint32_t lampa=0;


void portini()
{
	DDRA=0xff ; //relay kimenet
	DDRC=0xff ; //relay kimenet
	DDRD=(1<<PD7)|(1<<PD6)|(1<<PD5); //relay kimenet
	DDRG=(1<<PG2)|(1<<PG4); // PG LED ek
	DDRF=0;
	DDRE=0;
	DDRB=0;
}

void relay_out (uint32_t relay, uint8_t func)
{
	relayout=relay;
	
	if(func==3) //XOR
		{
		PORTA^=relayout;
		PORTC^=(relayout>>8);
		PORTD^=(relayout>>16);
		}

	if(func==1) // OR
		{
		PORTA|=relayout;
		PORTC|=(relayout>>8);
		PORTD|=(relayout>>16);
		}

	if(func==0) //AND
		{
		PORTA&=~relayout;
		PORTC&=~(relayout>>8);
		PORTD&=~(relayout>>16);
		}

}

void ledblink(uint8_t blinkfreq)
{
	tmpled++;
	
	if (tmpled>blinkfreq)
	{
		tmpled=0;
		PORTG^=(1<<PG2);
	}
}

void timer_setrelayfunc()
{
	if (INPF7) PF7timer++; //gombnyomási mérése
		
	if (PF7timer==PUSHTIME) //ha az ido eltelt bekapcsolja a kimenetet ezzel jelzi
		{
			PF7startidozito=0; // hogyan idozitsek ? hosszu vagy rovid gombnyomásra ?
			
			PF7lampa=3;
			PF6lampa==3;
			PF5lampa==3;
			
			relay_out(RelayPA0,1);
			relay_out(RelayPA1,1);
			relay_out(RelayPA2,1);
		}
		



	if(INPF7 && PF7gny==0 ) //lenyomas gomb
	{
		PF7gny=1;
		PF7timer=0;
		PF7startidozito=1;
		PF7tim=0;			  // hogyan idozitsek ? hosszu vagy rovid gombnyomásra ?
	}

	if((!INPF7) && PF7gny==1) //felengedés
	{
	PF7gny=0;
		if (PF7timer>=PUSHTIME)
		{
		PF7timer=0;
		PF7tim=0;
		}
		else 
		{
		PF7timer=0;

			switch(PF7lampa)
			{	case 0:
					{
					PF7lampa=1;
					if (PF5lampa==0) PF5lampa=3;
					if (PF6lampa==0) PF6lampa=3;
					relay_out(RelayPA0,1);
					relay_out(RelayPA1,1);
					relay_out(RelayPA2,1);
					break;
					}
				
				case 1:
					{
					PF7lampa=0;
					
					relay_out(RelayPA0,0);
					if (PF6lampa==3){relay_out(RelayPA1,0);PF6lampa=0;}
					if (PF5lampa==3){relay_out(RelayPA2,0);PF5lampa=0;}
					PF7startidozito=0;
					PF7tim=0;	
					break;
					}
			
				case 3:
					{
					PF7lampa=0;
					relay_out(RelayPA0,0);
					if (PF6lampa==0){relay_out(RelayPA1,0);}
					if (PF5lampa==0){relay_out(RelayPA2,0);}
					if (PF6lampa==3){relay_out(RelayPA1,0);PF6lampa=0;}
					if (PF5lampa==3){relay_out(RelayPA2,0);PF5lampa=0;}
					break;
					}
				default: break;
			}
		}
	}
	
	
	if (PF7startidozito==1) // késleltett ido kikapcsolás engedélyezése
	{
		PF7tim++;
		if (PF7tim==PF7TIMER)  // mennyi ido után kapcsoljon ki
		{
			PF7tim=0;
			PF7lampa=0;
			relay_out(RelayPA0,0);
			if (PF6lampa==3) 
				{
				relay_out(RelayPA1,0);
				PF6lampa=0;
				}
			if (PF5lampa==3)
				{
				relay_out(RelayPA2,0);
				PF5lampa=0;
				}
		}
	}







	if(INPF6 && PF6gny==0 ) //lenyomas gomb
	{
		PF6gny=1;
	}

	if((!INPF6) && PF6gny==1) //felengedés
	{
		PF6gny=0;
		
			if (PF6lampa==0)
			{
			PF6lampa=1;
			relay_out(RelayPA1,1);
			}
			else
			{
			PF6lampa=0;
			relay_out(RelayPA1,0);	
			}
	}
	
	
	
	
	
	
	
	if(INPF5 && PF5gny==0 ) //lenyomas gomb
	{
		PF5gny=1;
	}

	if((!INPF5) && PF5gny==1) //felengedés
	{
		PF5gny=0;
		
		if (PF5lampa==0)
		{
			PF5lampa=1;
			relay_out(RelayPA2,1);
		}
		else
		{
			PF5lampa=0;
			relay_out(RelayPA2,0);
		}
	}
	

}

void set_relay(uint8_t readpin, uint32_t setrelay, uint8_t intmp, char *mqttcommand)
{
	if(readpin && !(gny&((uint32_t)1<<intmp)) ) //lenyomas gomb
	{
		gny=gny|((uint32_t)1<<intmp);
	}

	if(!(readpin) && (gny&((uint32_t)1<<intmp)) ) //felengedés
	{
		gny=gny&(~((uint32_t)1<<intmp));
		
		if ( !(lampa&((uint32_t)1<<intmp)) )
		{	
			USART0_putstring(mqttcommand);
			USART1_putstring(mqttcommand);
			USART0_putstring(":ON\n");
			USART1_putstring(":ON\n\r");
			lampa|=((uint32_t)1<<intmp);
			relay_out(setrelay,1);
		}
		else
		{	
			USART0_putstring(mqttcommand);
			USART1_putstring(mqttcommand);
			USART0_putstring(":OFF\n");
			USART1_putstring(":OFF\n\r");
			lampa&=(~((uint32_t)1<<intmp));
			relay_out(setrelay,0);
		}
	}
	

}

void set_relay_mqtt (char* topic,char* state)
{
	
	uint32_t setrelay=0;
	uint8_t intmp=0;
 	
	if (strcmp(topic,"PA3")==0) {setrelay=RelayPA3; intmp=TMPPF4;}
	if (strcmp(topic,"PA4")==0) {setrelay=RelayPA4; intmp=TMPPF3;}
	if (strcmp(topic,"PA5")==0) {setrelay=RelayPA5; intmp=TMPPF2;}
	if (strcmp(topic,"PA6")==0) {setrelay=RelayPA6; intmp=TMPPF1;}
	if (strcmp(topic,"PA7")==0) {setrelay=RelayPA7; intmp=TMPPF0;}
	
	if (strcmp(topic,"PC0")==0) {setrelay=RelayPC0; intmp=TMPPE7;}
	if (strcmp(topic,"PC1")==0) {setrelay=RelayPC1; intmp=TMPPE6;}
	if (strcmp(topic,"PC2")==0) {setrelay=RelayPC2; intmp=TMPPE5;}
	if (strcmp(topic,"PC3")==0) {setrelay=RelayPC3; intmp=TMPPE4;}
	if (strcmp(topic,"PC4")==0) {setrelay=RelayPC4; intmp=TMPPE3;}
	if (strcmp(topic,"PC5")==0) {setrelay=RelayPC5; intmp=TMPPE2;}	
	if (strcmp(topic,"PC6")==0) {setrelay=RelayPC6; intmp=TMPPE1;}
	if (strcmp(topic,"PC7")==0) {setrelay=RelayPC7; intmp=TMPPE0;}
		
	if (strcmp(topic,"PD5")==0) {setrelay=RelayPD5; intmp=TMPPB7;}
	if (strcmp(topic,"PD6")==0) {setrelay=RelayPD6; intmp=TMPPB6;}
	if (strcmp(topic,"PD7")==0) {setrelay=RelayPD7; intmp=TMPPB5;}


	if (strcmp(state,"ON")==0 )
		{
		lampa|=((uint32_t)1<<intmp);
		relay_out(setrelay,1);
		}
	
	if(strcmp(state,"OFF")==0)
		{
		lampa&=(~((uint32_t)1<<intmp));
		relay_out(setrelay,0);
		}
	

}

