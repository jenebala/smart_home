/*
 * IncFile1.h
 *
 * Created: 2019. 04. 20. 9:49:28
 *  Author: Jenei Balazs
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define F_CPU 16000000UL

#define Status_PA1 (!(lampa&((uint32_t)1<<TMPPF6)))  // ha on akkor nem igaz
#define Setstatus_PA1 (lampa|=((uint32_t)1<<TMPPF6)) // status beállitása

#define Status_PA2 (!(lampa&((uint32_t)1<<TMPPF5)))

#define RelayPA0 1
#define RelayPA1 2
#define RelayPA2 4
#define RelayPA3 8
#define RelayPA4 16
#define RelayPA5 32
#define RelayPA6 64
#define RelayPA7 128
#define RelayPC0 256
#define RelayPC1 512
#define RelayPC2 1024
#define RelayPC3 2048
#define RelayPC4 4096
#define RelayPC5 8192
#define RelayPC6 16384
#define RelayPC7 32768
#define RelayPD5 0x200000
#define RelayPD6 0x400000
#define RelayPD7 0x800000


#define PUSHTIME 7 //hosszu gombnyomások definiálása 700 ms 

#define PF7TIMER 1400 // másodperc mennyi ideig legyen bekapcsolva ?


#define TMPPF7 7
#define TMPPF6 6
#define TMPPF5 5
#define TMPPF4 4
#define TMPPF3 3
#define TMPPF2 2
#define TMPPF1 1
#define TMPPF0 0

#define TMPPE7 15
#define TMPPE6 14
#define TMPPE5 13
#define TMPPE4 12
#define TMPPE3 11
#define TMPPE2 10
#define TMPPE1 9
#define TMPPE0 8

#define TMPPB7 23
#define TMPPB6 22
#define TMPPB5 21
#define TMPPB4 20
#define TMPPB3 19
#define TMPPB2 18
#define TMPPB1 17
#define TMPPB0 16


#define INPF7 ((~PINF)&(1<<PF7))
#define INPF6 ((~PINF)&(1<<PF6))
#define INPF5 ((~PINF)&(1<<PF5))
#define INPF4 ((~PINF)&(1<<PF4))
#define INPF3 ((~PINF)&(1<<PF3))
#define INPF2 ((~PINF)&(1<<PF2))
#define INPF1 ((~PINF)&(1<<PF1))
#define INPF0 ((~PINF)&(1<<PF0))

#define INPE7 ((~PINE)&(1<<PE7))
#define INPE6 ((~PINE)&(1<<PE6))
#define INPE5 ((~PINE)&(1<<PE5))
#define INPE4 ((~PINE)&(1<<PE4))
#define INPE3 ((~PINE)&(1<<PE3))
#define INPE2 ((~PINE)&(1<<PE2))
#define INPE1 ((~PIND)&(1<<PD4))
#define INPE0 ((~PIND)&(1<<PD1))

#define INPB7 ((~PINB)&(1<<PB7))
#define INPB6 ((~PINB)&(1<<PB6))
#define INPB5 ((~PINB)&(1<<PB5))
#define INPB4 ((~PINB)&(1<<PB4))
#define INPB3 ((~PINB)&(1<<PB3))
#define INPB2 ((~PINB)&(1<<PB2))
#define INPB1 ((~PINB)&(1<<PB1))
#define INPB0 ((~PINB)&(1<<PB0))

#define INPG0 ((~PING)&(1<<PG0))
#define INPG1 ((~PING)&(1<<PG1))



#endif /* INCFILE1_H_ */