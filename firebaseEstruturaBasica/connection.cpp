#include "connection.h"

bool stationInitialized = false;
bool stationConnected = false;

void wifiInitialize(){

	WiFi.persistent(false);

	println("-------------- wifiInitialize ------------");

	// Connect to WiFi access point
	stationInitialized = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	// Check if connection errors
	if(!stationInitialized){
		println("Error, unable to connect specified WiFi network.");
	}
}

void connectWifi(){

	println("-------------- connectWifi ------------");

	connectWifi(MAXIMUM_ATTEMPT_CONNECTION_DEFAULT);
}

void connectWifi(int maximum_attempt){

	println("-------------- connectWifi 2 ------------");

	int currentAttempt = 0;

	// Wait connection completed
	print("Connecting to AP...");
	while(WiFi.status() != WL_CONNECTED && currentAttempt++ < maximum_attempt){
		delayMilliSeconds(500);
		print(".");
	}

	stationConnected = (WiFi.status() == WL_CONNECTED);

	print("\nStatus conexao: ");
	println(WiFi.status());

	print("Ok\n");
}

bool pingOK(){
	setPingBusy(true);
	println("\n\nPinging google ip 8.8.8.8");
	return pinger.Ping(IPAddress(8,8,8,8), 1);
}

//gets e sets

bool getStationInitialized(){
	return stationInitialized;
}

void setStationInitialized(bool value){
	stationInitialized = value;
}

bool getStationConnected(){
	return stationConnected;
}

void setStationConnected(bool value){
	stationConnected = value;
}
