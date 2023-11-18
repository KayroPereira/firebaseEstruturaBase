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

		pingBusy = false;
//	    statusPing = response.ReceivedResponse;


	    if (response.ReceivedResponse){
	    	statusPing = true;
			stateChange = true;
//	    	if(!statusPing){
//	    		statusPing = true;
//				stateChange = true;
//			}
	    }else{
	    	statusPing = false;
			stateChange = true;
//	    	if(statusPing){
//	    		statusPing = false;
//				stateChange = true;
//			}
	    }

		Serial.printf("\n\n####### statusPing: %s -> stateChange: %s -> pingBusy: %s\n", statusPing ? "true" : "false", stateChange ? "true" : "false", pingBusy ? "true" : "false");
	    // Return true to continue the ping sequence.
	    // If current event returns false, the ping sequence is interrupted.
	    return true;
	});
}

void pingerEnd(){
	pinger.OnEnd([](const PingerResponse& response){
		Serial.printf("\n\n ***************** pingBusy: %s\n", pingBusy ? "true" : "false");
	    return true;
	});
}

void setPingBusy(bool value){
	pingBusy = value;
}

bool getPingBusy(){
	return pingBusy;
}
