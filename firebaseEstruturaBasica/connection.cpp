#include "connection.h"

bool stationInitialized = false;
bool stationConnected = false;

void wifiInitialize(){

	WiFi.persistent(false);

	Serial.println("-------------- wifiInitialize ------------");

	// Connect to WiFi access point
	stationInitialized = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	// Check if connection errors
	if(!stationInitialized){
		Serial.println("Error, unable to connect specified WiFi network.");
	}
}

void connectWifi(){

	Serial.println("-------------- connectWifi ------------");

	connectWifi(MAXIMUM_ATTEMPT_CONNECTION_DEFAULT);
}

//void wait(unsigned long time) {
//    unsigned long start=millis();
//    while(millis()-start < time) {
//        yield();
//    };
//}

void connectWifi(int maximum_attempt){

	Serial.println("-------------- connectWifi 2 ------------");

	int currentAttempt = 0;

	// Wait connection completed
	Serial.print("Connecting to AP...");
	while(WiFi.status() != WL_CONNECTED && currentAttempt++ < maximum_attempt){
//	while(WiFi.status() != WL_CONNECTED){
		delay(500);
//		wait(500);
//		yield();
		Serial.print(".");
	}

	stationConnected = (WiFi.status() == WL_CONNECTED);

	Serial.print("\nStatus conexao: ");
	Serial.println(WiFi.status());

	Serial.print("Ok\n");
}

bool pingOK(){
	setPingBusy(true);
	Serial.printf("\n\nPinging google ip 8.8.8.8\n");
	return pinger.Ping(IPAddress(8,8,8,8), 1);
}
