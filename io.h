/*
 * io.h
 *
 * Created: 2019. 04. 21. 20:28:24
 *  Author: Jenei Balazs
 */ 
#include <avr/io.h>



#ifndef IO_H_
#define IO_H_

void portini();
void relay_out (uint32_t relay, uint8_t func);
void ledblink(uint8_t blinkfreq);
void timer_setrelayfunc();
void set_relay(uint8_t readpin,uint32_t setrelay,uint8_t intmp,char *mqttcommand);
void set_relay_mqtt(char* topic,char* state);

#endif /* IO_H_ */