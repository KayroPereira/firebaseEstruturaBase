#include "testWiFiPingV1.h"

void variableInitialize(){
	println("-------------- variableInitialize ------------");
	setConnectionHealth(false);
	reloadRegDelayPing();
}

void setup(){

	// Begin serial connection at 115200 baud
	serialInitialize(115200);
	println("\n\nInicializando....");

	initializeHardware();
	variableInitialize();

	delayMilliSeconds(2000);
}

long sendDataPrevMillis1 = getMillis();

void loop(){

	if(!getInitializationOk()){
		communicationBoot();
	}else{
		if (getMillis() - sendDataPrevMillis1 > 100){
			togglePin(LED_BUILTIN);
			sendDataPrevMillis1 = getMillis();
		}

		if(!getConnectionHealth()){
			startCheckHealthConnection();
		}else{


			sendDataFirebase();
		}
	}

	if(getCheckHealthConnection() && getStartPing()){
		setStartPing(false);
		healthConnection();
	}
}
