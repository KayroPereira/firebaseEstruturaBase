#include "accessHardware.h"

unsigned long delayTryCommunication = getMillis();

//TODO - converter para flags
bool initializationOk = false;
bool connectionHealth = false;
bool checkHealthConnection = false;
bool flgFirstBootAttempt = false;
bool flgFirebaseConfigured = false;

void initializeHardware(){

	println("-------------- initializeHardware ------------");

	timer1Configuration();

	communicationBoot();

	pingerReceive();
	pingerEnd();

//	firebaseConfiguration();

	flgFirstBootAttempt = true;

	pinConfiguration(LED_BUILTIN, OUTPUT);

//	wifiInitialize();
//
//	if(stationInitialized){
//		connectWifi();
//	}
}

void communicationBoot(){

	if((getMillis() - delayTryCommunication) > DELAY_TRY_COMMUNICATION){
		println("\n-------------- communicationBoot ------------");
		delayTryCommunication = getMillis();
	}else{
		return;
	}

	if(!getStationInitialized()){
		wifiInitialize();
	}

	if(getStationInitialized() && !getStationConnected()){
		if(!flgFirstBootAttempt){
			connectWifi();
		}else{
			connectWifi(5);
		}
	}

	if(getStationConnected() && !connectionHealth){

		systemInformation();

		startCheckHealthConnection();
	}

	initializationOk = (getStationInitialized() && getStationConnected() && getConnectionHealth());

	if(initializationOk && !flgFirebaseConfigured){
		firebaseConfiguration();
		flgFirebaseConfigured = true;
	}

	Serial.printf("\ninitializationOk: %s\n", initializationOk ? "true" : "false");
}

void systemInformation(){

	//Ping default gateway
	Serial.printf("\n\nPinging default gateway with IP %s\n", WiFi.gatewayIP().toString().c_str());

	print("\nConnected with IP: ");
	Serial.println(WiFi.localIP());

	Serial.printf("\n\nFirebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
}

void startCheckHealthConnection(){
	if(!getFlgRegDelayPing()){
		println("-------------- startCheckHealthConnection ------------");
		reloadRegDelayPing();
		setFlgRegDelayPing(true);
		setCheckHealthConnection(true);
	}
}

void stopCheckHealthConnection(){
	println("-------------- stopCheckHealthConnection ------------");
	setFlgRegDelayPing(false);
	setCheckHealthConnection(false);
	reloadRegDelayPing();
}

//TODO - Remover
int contPing = 0;

void healthConnection(){

	if(contPing % 10 == 0)
		println("\n-------------- healthConnection ------------");

	if(getStateChange()){
		print("Ping ok: ");
		print((getStatusPing() ? "true -> " : "false -> "));
		println(contPing++);
		print("stateChange ok: ");
		println((getStateChange() ? "true -> " : "false -> "));
	}

	if(getStateChange() && getStatusPing()){
		setConnectionHealth(true);
		setStateChange(false);

		//TODO - Verificar necessidade
//		firebaseConfiguration();

//		beginStreamCallback();
	}else if(getStateChange() && !getStatusPing()){
		setConnectionHealth(false);
		setStateChange(false);
//		removeStreamCallback();
	}

	if(getStateChange()){
		Serial.printf("\n\n getPingBusy: %s -> getConnectionHealth: %s\n", getPingBusy() ? "true" : "false", getConnectionHealth() ? "true" : "false");
	}

	if(!getPingBusy() && !getConnectionHealth()){
		pingOK();
	}
}

//funções acesso ao hardware

void pinConfiguration(uint8_t pin, uint8_t mode){
	pinMode(pin, mode);
}

void pinWrite(uint8_t pin, uint8_t val){
	digitalWrite(pin, val);
}

int pinRead(uint8_t pin){
	return digitalRead(pin);
}

void setPin(uint8_t pin){
	pinWrite(pin, HIGH);
}

void clearPin(uint8_t pin){
	pinWrite(pin, LOW);
}

void togglePin(uint8_t pin){
	pinWrite(pin, !pinRead(pin));
}

void serialInitialize(unsigned long baud){
	Serial.begin(baud);
}

void println(const char c[]){
	Serial.println(c);
}

void println(int num){
    Serial.println(num);
}

void print(const char c[]){
	Serial.print(c);
}

void delayMilliSeconds(unsigned long ms){
	delay(ms);
}

unsigned long getMillis(){
	return millis();
}

//gets e sets

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

bool getInitializationOk(){
	return initializationOk;
}

void setInitializationOk(bool value){
	initializationOk = value;
}
