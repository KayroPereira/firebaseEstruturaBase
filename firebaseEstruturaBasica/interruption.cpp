#include "interruption.h"

//int count = 0;
int regDelayPing;

bool startPing = true;
bool flgRegDelayPing = false;

void timerInterrupt(){
//	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

	if(getFlgRegDelayPing() && !--regDelayPing){
		reloadRegDelayPing();
	    setStartPing(true);
	}

	if(getCheckHealthConnection() && getStartPing()){
		setStartPing(false);
		healthConnection();
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

bool getStartPing(){
	return startPing;
}

void setStartPing(bool value){
	startPing = value;
}

bool getFlgRegDelayPing(){
	return flgRegDelayPing;
}

void setFlgRegDelayPing(bool value){
	flgRegDelayPing = value;
}
