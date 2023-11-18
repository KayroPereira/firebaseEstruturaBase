#include "accessHardware.h"


//TODO - converter para flagsd
bool initializationOk = false;
bool connectionHealth = false;
bool checkHealthConnection = false;
bool flgFirstBootAttempt = false;
bool flgFirebaseConfigured = false;

void initializeHardware(){
	Serial.println("-------------- initializeHardware ------------");

	timer1Configuration();

	communicationBoot();

	pingerReceive();
	pingerEnd();

//	firebaseConfiguration();

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

	if(stationInitialized && !stationConnected){
		if(!flgFirstBootAttempt){
			connectWifi();
		}else{
			connectWifi(5);
		}
	}

	if(stationConnected && !connectionHealth){
//		delay(1000);
//		pingerReceive();
//		pingerEnd();
//		delay(1000);

		startCheckHealthConnection();
	}

	initializationOk = (stationInitialized && stationConnected && getConnectionHealth());

	if(initializationOk && !flgFirebaseConfigured){
		firebaseConfiguration();
		flgFirebaseConfigured = true;
	}

	Serial.printf("\ninitializationOk: %s\n", initializationOk ? "true" : "false");
}

void systemInformation(){

	// Ping default gateway
//	Serial.printf("\n\nPinging default gateway with IP %s\n", WiFi.gatewayIP().toString().c_str());
//	if(pinger.Ping(WiFi.gatewayIP()) == false){
//		Serial.println("Error during last ping command.");
//	}
//
//	Serial.println();
//	Serial.print("Connected with IP: ");
//	Serial.println(WiFi.localIP());
//	Serial.println();
//
//	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
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

	Serial.print("Ping ok: ");
	Serial.print((statusPing ? "true -> " : "false -> "));
	Serial.println(contPing++);
	Serial.print("stateChange ok: ");
	Serial.println((stateChange ? "true -> " : "false -> "));

	if(stateChange && statusPing){
		setConnectionHealth(true);
		stateChange = false;

		//TODO - Verificar necessidade
//		firebaseConfiguration();

		beginStreamCallback();
	}else if(stateChange && !statusPing){
		setConnectionHealth(false);
		stateChange = false;
//		removeStreamCallback();
	}

	Serial.printf("\n\n getPingBusy: %s -> getConnectionHealth: %s\n", getPingBusy() ? "true" : "false", getConnectionHealth() ? "true" : "false");

	if(!getPingBusy() && !getConnectionHealth()){
		pingOK();
	}

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
