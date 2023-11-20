#include "accessHardware.h"

unsigned long delayTryCommunication = getMillis();

union{
	struct{
		unsigned int initializationOk: 1;
		unsigned int connectionHealth: 1;
		unsigned int checkHealthConnection: 1;
		unsigned int flgFirstBootAttempt: 1;
		unsigned int flgFirebaseConfigured: 1;
	}flgsAccessHardwareBits;

	unsigned int flgsAccessHardware;
}flgsAccessHardware;

void initializeHardware(){

	flgsAccessHardware.flgsAccessHardware = 0;

	timer1Configuration();

	communicationBoot();

	pingerReceive();
	pingerEnd();

	flgsAccessHardware.flgsAccessHardwareBits.flgFirstBootAttempt = true;

	pinConfiguration(LED_BUILTIN, OUTPUT);
}

void communicationBoot(){

	if((getMillis() - delayTryCommunication) > DELAY_TRY_COMMUNICATION){
		delayTryCommunication = getMillis();
	}else{
		return;
	}

	if(!getStationInitialized()){
		wifiInitialize();
	}

	if(getStationInitialized() && !getStationConnected()){
		if(!flgsAccessHardware.flgsAccessHardwareBits.flgFirstBootAttempt){
			connectWifi();
		}else{
			connectWifi(5);
		}
	}

	if(getStationConnected() && !flgsAccessHardware.flgsAccessHardwareBits.connectionHealth){
		startCheckHealthConnection();
	}

	flgsAccessHardware.flgsAccessHardwareBits.initializationOk = (getStationInitialized() && getStationConnected() && getConnectionHealth());

	if(flgsAccessHardware.flgsAccessHardwareBits.initializationOk && !flgsAccessHardware.flgsAccessHardwareBits.flgFirebaseConfigured){

		systemInformation();

		firebaseConfiguration();
		flgsAccessHardware.flgsAccessHardwareBits.flgFirebaseConfigured = true;
	}
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
		reloadRegDelayPing();
		setFlgRegDelayPing(true);
		setCheckHealthConnection(true);
	}
}

void stopCheckHealthConnection(){
	setFlgRegDelayPing(false);
	setCheckHealthConnection(false);
	reloadRegDelayPing();
}

void healthConnection(){

	if(getStateChange() && getStatusPing()){
		setConnectionHealth(true);
		setStateChange(false);

		starStreamCallback();
	}else if(getStateChange() && !getStatusPing()){
		setConnectionHealth(false);
		setStateChange(false);
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

void setFlgsAccessHardware(unsigned int value){
	flgsAccessHardware.flgsAccessHardware = value;
}

void setConnectionHealth(bool value){
	flgsAccessHardware.flgsAccessHardwareBits.connectionHealth = value;

	if(!value){
		startCheckHealthConnection();
	}else{
		stopCheckHealthConnection();
	}
}

bool getConnectionHealth(){
	return flgsAccessHardware.flgsAccessHardwareBits.connectionHealth;
}

bool getCheckHealthConnection(){
	return flgsAccessHardware.flgsAccessHardwareBits.checkHealthConnection;
}

void setCheckHealthConnection(bool value){
	flgsAccessHardware.flgsAccessHardwareBits.checkHealthConnection = value;
}

bool getInitializationOk(){
	return flgsAccessHardware.flgsAccessHardwareBits.initializationOk;
}

void setInitializationOk(bool value){
	flgsAccessHardware.flgsAccessHardwareBits.initializationOk = value;
}
