#include "PingUtils.h"

// Set global to avoid object removing after setup() routine
Pinger pinger;

union{
	struct{
		unsigned int statusPing: 1;
		unsigned int stateChange: 1;
		unsigned int pingBusy: 1;
	}flgsPingUtilsBits;

	unsigned int flgsPingUtils;
}flgsPingUtils;

void pingerReceive(){
	pinger.OnReceive([](const PingerResponse& response){

		flgsPingUtils.flgsPingUtilsBits.statusPing = response.ReceivedResponse;

		flgsPingUtils.flgsPingUtilsBits.stateChange = true;

	    // Return true to continue the ping sequence.
	    // If current event returns false, the ping sequence is interrupted.
	    return true;
	});
}

void pingerEnd(){
	pinger.OnEnd([](const PingerResponse& response){
		flgsPingUtils.flgsPingUtilsBits.pingBusy = false;
	    return true;
	});
}

//gets e sets

void setFlgsPingUtils(unsigned int value){
	flgsPingUtils.flgsPingUtils = value;
}

bool getStatusPing(){
	return flgsPingUtils.flgsPingUtilsBits.statusPing;
}

void setStatusPing(bool value){
	flgsPingUtils.flgsPingUtilsBits.statusPing = value;
}

bool getStateChange(){
	return flgsPingUtils.flgsPingUtilsBits.stateChange;
}

void setStateChange(bool value){
	flgsPingUtils.flgsPingUtilsBits.stateChange = value;
}

void setPingBusy(bool value){
	flgsPingUtils.flgsPingUtilsBits.pingBusy = value;
}

bool getPingBusy(){
	return flgsPingUtils.flgsPingUtilsBits.pingBusy;
}
