#include "accessHardware.h"


//TODO - converter para flagsd
bool initializationOk = false;
bool connectionHealth = false;
bool checkHealthConnection = false;
bool flgFirstBootAttempt = false;

void initializeHardware(){
	Serial.println("-------------- initializeHardware ------------");

	timer1Configuration();

	pingerReceive();
	pingerEnd();

	firebaseConfiguration();

	communicationBoot();

	flgFirstBootAttempt = true;

//	wifiInitialize();
//
//	if(stationInitialized){
//		connectWifi();
//	}
}

unsigned long delayTryCommunication = millis();
#define DELAY_TRY_COMMUNICATION			2000

void communicationBoot(){

	if((millis() - delayTryCommunication) > DELAY_TRY_COMMUNICATION){
		Serial.println("\n-------------- communicationBoot ------------");
		delayTryCommunication = millis();
	}else{
		return;
	}

	if(!stationInitialized){
		wifiInitialize();
	}

	if(!stationConnected){
		if(!flgFirstBootAttempt){
			connectWifi();
		}else{
			connectWifi(3);
		}
	}

	if(!connectionHealth){
		startCheckHealthConnection();
	}

	initializationOk = (stationInitialized && stationConnected && getConnectionHealth());

	Serial.printf("\ninitializationOk: %s\n", initializationOk ? "true" : "false");
}

void systemInformation(){

	// Ping default gateway
	Serial.printf("\n\nPinging default gateway with IP %s\n", WiFi.gatewayIP().toString().c_str());
	if(pinger.Ping(WiFi.gatewayIP()) == false){
		Serial.println("Error during last ping command.");
	}

	Serial.println();
	Serial.print("Connected with IP: ");
	Serial.println(WiFi.localIP());
	Serial.println();

	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
}

//TODO - Remover
int contPing = 0;

void startCheckHealthConnection(){
	if(!getFlgRegDelayPing()){
		Serial.println("-------------- startCheckHealthConnection ------------");
		reloadRegDelayPing();
		setFlgRegDelayPing(true);
		setCheckHealthConnection(true);
	}
}

void stopCheckHealthConnection(){
	Serial.println("-------------- stopCheckHealthConnection ------------");
	setFlgRegDelayPing(false);
	setCheckHealthConnection(false);
	reloadRegDelayPing();
}

void healthConnection(){

	Serial.println("\n-------------- healthConnection ------------");


	if(stateChange && statusPing){
		setConnectionHealth(true);
		stateChange = false;
		beginStreamCallback();
	}else if(stateChange && !statusPing){
		setConnectionHealth(false);
		stateChange = false;
		removeStreamCallback();
	}

	if(!getPingBusy() && !getConnectionHealth()){
		pingOK();
	}

	Serial.print("Ping ok: ");
	Serial.print((statusPing ? "true -> " : "false -> "));
	Serial.println(contPing++);
	Serial.print("stateChange ok: ");
	Serial.println((stateChange ? "true -> " : "false -> "));
}


void setConnectionHealth(bool value){
	connectionHealth = value;

	if(!value){
		startCheckHealthConnection();
	}else{
		stopCheckHealthConnection();
	}
}

bool getConnectionHealth(){
	return connectionHealth;
}

bool getCheckHealthConnection(){
	return checkHealthConnection;
}

void setCheckHealthConnection(bool value){
	checkHealthConnection = value;
}
