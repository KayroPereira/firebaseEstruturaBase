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

long temp = getMillis();
long temp1 = getMillis();

void loop(){

	if (getMillis() - sendDataPrevMillis1 > 100){
		togglePin(LED_BUILTIN);
		sendDataPrevMillis1 = getMillis();
	}

	if(!getInitializationOk()){
		if (getMillis() - temp > 1500){

			temp = getMillis();
			println("main step 1 ------->");
		}

		communicationBoot();
	}else{

		if (getMillis() - temp1 > 1500){
			println("main step 2 ------->");
		}

		if(!getConnectionHealth()){
			if (getMillis() - temp1 > 1500){
				println("main step 3 ------->");
			}
			startCheckHealthConnection();
		}else{
			if (getMillis() - temp1 > 1500){
				println("main step 4 ------->");
			}
			sendDataFirebase();
		}

		if (getMillis() - temp1 > 1500){
			temp1 = getMillis();
		}
	}

	if(getCheckHealthConnection() && getStartPing()){
		setStartPing(false);
		healthConnection();
	}
}
