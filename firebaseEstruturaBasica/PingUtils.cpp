#include "PingUtils.h"

//TODO - Remover
#include "Arduino.h"

// Set global to avoid object removing after setup() routine
Pinger pinger;

bool statusPing = false;
bool stateChange = false;
bool pingBusy = false;

void pingerReceive(){
	pinger.OnReceive([](const PingerResponse& response){

//		pingBusy = false;
	    statusPing = response.ReceivedResponse;

		stateChange = true;

		Serial.printf("\n\n####### statusPing: %s -> stateChange: %s -> pingBusy: %s\n", statusPing ? "true" : "false", stateChange ? "true" : "false", pingBusy ? "true" : "false");
	    // Return true to continue the ping sequence.
	    // If current event returns false, the ping sequence is interrupted.
	    return true;
	});
}

void pingerEnd(){
	pinger.OnEnd([](const PingerResponse& response){
		pingBusy = false;
		Serial.printf("\n\n ***************** pingBusy: %s\n", pingBusy ? "true" : "false");
	    return true;
	});
}

//gets e sets

bool getStatusPing(){
	return statusPing;
}

void setStatusPing(bool value){
	statusPing = value;
}

bool getStateChange(){
	return stateChange;
}

void setStateChange(bool value){
	stateChange = value;
}

void setPingBusy(bool value){
	pingBusy = value;
}

bool getPingBusy(){
	return pingBusy;
}
