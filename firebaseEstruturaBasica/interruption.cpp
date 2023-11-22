#include "interruption.h"

int regDelayPing;

union{
	struct{
		unsigned int startPing: 1;
		unsigned int flgRegDelayPing: 1;
	}flgsInterruptionBits;

	unsigned int flgsInterruption;
}flgsInterruption;

void timerInterrupt(){

	if(getFlgRegDelayPing() && !--regDelayPing){
		reloadRegDelayPing();
	    setStartPing(true);
	}
}

void timer1Configuration(){
	//Configurações timer1
	timer1_attachInterrupt(timerInterrupt);
	timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
	timer1_write((300 * BASE_TIME) / DIVISOR_TIMER); // 1 segundo (80 MHz / 256)
}

void reloadRegDelayPing(){
	regDelayPing = RELOAD_CONT;
}

//gets e sets

void setFlgsInterruption(unsigned int value){
	flgsInterruption.flgsInterruption = value;
}

bool getStartPing(){
	return flgsInterruption.flgsInterruptionBits.startPing;
}

void setStartPing(bool value){
	flgsInterruption.flgsInterruptionBits.startPing = value;
}

bool getFlgRegDelayPing(){
	return flgsInterruption.flgsInterruptionBits.flgRegDelayPing;
}

void setFlgRegDelayPing(bool value){
	flgsInterruption.flgsInterruptionBits.flgRegDelayPing = value;
}
