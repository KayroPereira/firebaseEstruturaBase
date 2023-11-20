#include "connection.h"

union{
	struct{
		unsigned int stationInitialized: 1;
		unsigned int stationConnected: 1;
	}flgsConnectionBits;

	unsigned int flgsConnection;
}flgsConnection;

void wifiInitialize(){

	WiFi.persistent(false);

	// Connect to WiFi access point
	flgsConnection.flgsConnectionBits.stationInitialized = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	// Check if connection errors
	if(!flgsConnection.flgsConnectionBits.stationInitialized){
		println("Error, unable to connect specified WiFi network.");
	}
}

void connectWifi(){

	connectWifi(MAXIMUM_ATTEMPT_CONNECTION_DEFAULT);
}

void connectWifi(int maximum_attempt){

	int currentAttempt = 0;

	// Wait connection completed
	print("Connecting to AP...");
	while(WiFi.status() != WL_CONNECTED && currentAttempt++ < maximum_attempt){
		delayMilliSeconds(500);
		print(".");
	}

	flgsConnection.flgsConnectionBits.stationConnected = (WiFi.status() == WL_CONNECTED);

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

void setFlgsConnection(unsigned int value){
	flgsConnection.flgsConnection = value;
}

bool getStationInitialized(){
	return flgsConnection.flgsConnectionBits.stationInitialized;
}

void setStationInitialized(bool value){
	flgsConnection.flgsConnectionBits.stationInitialized = value;
}

bool getStationConnected(){
	return flgsConnection.flgsConnectionBits.stationConnected;
}

void setStationConnected(bool value){
	flgsConnection.flgsConnectionBits.stationConnected = value;
}
