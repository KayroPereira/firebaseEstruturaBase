#include "PingUtils.h"

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
	    	if(!statusPing){
	    		statusPing = true;
				stateChange = true;
			}
	    }else{
	    	if(statusPing){
	    		statusPing = false;
				stateChange = true;
			}
	    }

	    // Return true to continue the ping sequence.
	    // If current event returns false, the ping sequence is interrupted.
	    return true;
	});
}

void pingerEnd(){
	pinger.OnEnd([](const PingerResponse& response){
	    return true;
	});
}

void setPingBusy(bool value){
	pingBusy = value;
}

bool getPingBusy(){
	return pingBusy;
}
