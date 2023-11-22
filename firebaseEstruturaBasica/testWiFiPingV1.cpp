#include "testWiFiPingV1.h"

void variableInitialize(){
	setFlgsAccessHardware(0);
	setFlgsPingUtils(0);
	setFlgsConnection(0);
	setFlgsInterruption(0);

	setConnectionHealth(false);
	reloadRegDelayPing();
}

void setup(){

	// Begin serial connection at 115200 baud
	serialInitialize(115200);
	println("\n\nInicializando....");

	variableInitialize();
	initializeHardware();

	delayMilliSeconds(2000);
}

long sendDataPrevMillis1 = getMillis();

void loop(){

	if (getMillis() - sendDataPrevMillis1 > 100){
		togglePin(LED_BUILTIN);
		sendDataPrevMillis1 = getMillis();
	}

	if(!getInitializationOk()){
		communicationBoot();
	}else{

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
