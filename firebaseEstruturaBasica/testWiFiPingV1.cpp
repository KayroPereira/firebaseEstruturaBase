//
//// Provide the token generation process info.
//#include <addons/TokenHelper.h>
//
//// Provide the RTDB payload printing info and other helper functions.
//#include <addons/RTDBHelper.h>

#include "testWiFiPingV1.h"

/* 1. Define the WiFi credentials */
//#define WIFI_SSID "kWiFiMobile"
//#define WIFI_PASSWORD "123456789"
// #define WIFI_SSID "NetWifi2"
// #define WIFI_PASSWORD "Pedepano21@@"


///* 2. Define the API Key */
//#define API_KEY "AIzaSyC2cvSAFq25npDjOD8Q1z7MhUPpiOMZl7A"
//
///* 3. Define the RTDB URL */
//#define DATABASE_URL "https://testfirebaseesp8266-a132a-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
//
///* 4. Define the user Email and password that alreadey registerd or added in your project */
//#define USER_EMAIL "teste@gmail.com"
//#define USER_PASSWORD "123456"

//// Define Firebase Data object
//FirebaseData stream;
//FirebaseData fbdo;
//
//FirebaseAuth auth;
//FirebaseConfig config;

//bool startPing = false;

//int count = 0;
//int cont = RELOAD_CONT;
//int contPing = 0;

//volatile bool dataChanged = false;
//
//void streamCallback(StreamData data) {
//	Serial.printf("stream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\n\n",
//				data.streamPath().c_str(),
//				data.dataPath().c_str(),
//				data.dataType().c_str(),
//				data.eventType().c_str());
//	printResult(data); // see addons/RTDBHelper.h
//	Serial.println();
//
//	Serial.printf("Received stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());
//
//	dataChanged = true;
//}
//
//void streamTimeoutCallback(bool timeout) {
//	if (!stream.httpConnected())
//	  Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
//
//	if (timeout) {
//		Serial.println("stream timed out, resuming...\n");
//		Firebase.removeStreamCallback(stream);
//		setConnectionHealth(false);
//	}
//}

void variableInitialize(){
	Serial.println("-------------- variableInitialize ------------");
//	setStartPing(true);
	setConnectionHealth(false);
	reloadRegDelayPing();
}

void setup(){

	// Begin serial connection at 9600 baud
	Serial.begin(9600);
	Serial.println("\n\nInicializando....");

	delay(2000);

	initializeHardware();
	variableInitialize();

////	 Connect to WiFi access point
//	bool stationConnected = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//	// Check if connection errors
//	if(!stationConnected){
//		Serial.println("Error, unable to connect specified WiFi network.");
//	}
//
//	// Wait connection completed
//	Serial.print("Connecting to AP...");
//	while(WiFi.status() != WL_CONNECTED){
//		delay(500);
//		Serial.print(".");
//	}
//	Serial.print("Ok\n");




//	pingerReceive();
//	pingerEnd();


//	// Ping default gateway
//	Serial.printf("\n\nPinging default gateway with IP %s\n", WiFi.gatewayIP().toString().c_str());
//	if(pinger.Ping(WiFi.gatewayIP()) == false){
//		Serial.println("Error during last ping command.");
//	}

//	//Configurações timer
//	timer1_attachInterrupt(timerInterrupt);
//	timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
//	timer1_write((300 * BASE_TIME) / DIVISOR_TIMER); // 1 segundo (80 MHz / 256)

//	Serial.println();
//	Serial.print("Connected with IP: ");
//	Serial.println(WiFi.localIP());
//	Serial.println();
//
//	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

//	/* Assign the api key (required) */
//	config.api_key = API_KEY;
//
//	/* Assign the user sign in credentials */
//	auth.user.email = USER_EMAIL;
//	auth.user.password = USER_PASSWORD;
//
//	/* Assign the RTDB URL (required) */
//	config.database_url = DATABASE_URL;
//
//	/* Assign the callback function for the long running token generation task */
//	config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
//
//	Firebase.begin(&config, &auth);
//
//	Firebase.reconnectWiFi(true);
//
//	#if defined(ESP8266)
//		stream.setBSSLBufferSize(2048 /* Rx in bytes, 512 - 16384 */, 512 /* Tx in bytes, 512 - 16384 */);
//	#endif

//	if (!Firebase.beginStream(stream, "/test/stream/data"))
//		Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());
//
//	Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);

	pinMode(LED_BUILTIN, OUTPUT);
}

//unsigned long sendDataPrevMillis = 0;
//long sendDataPrevMillis1 = millis();
//long sendDataPrevMillis2 = millis();


void loop(){

	if(!initializationOk){
		communicationBoot();
	}else{

		if(!getConnectionHealth()){
			startCheckHealthConnection();
		}else{
//			//		connectWifi(3);
//			// Ping default gateway
//			if((millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)){
//
//				sendDataPrevMillis = millis();
//
//				Serial.printf("\n\nPinging default gateway with IP %s\n", WiFi.gatewayIP().toString().c_str());
//				if(pinger.Ping(WiFi.gatewayIP()) == false){
//					Serial.println("Error during last ping command.");
//				}else{
//					Serial.println("Conexao ok!");
//					stationConnected = true;
//				}
//			}
//		}else{
//	//		if(startPing){
//	//			startPing = false;
//	//
//	//			pingOK();
//	//
//	//			Serial.print("Ping ok: ");
//	//			Serial.print((statusPing ? "true -> " : "false -> "));
//	//			Serial.println(contPing++);
//	//			Serial.print("stateChange ok: ");
//	//			Serial.println((stateChange ? "true -> " : "false -> "));
//	//		}

//			if(stateChange && statusPing){
//
//				if (!Firebase.beginStream(stream, "/test/stream/data")) {
//				  Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());
//				}
//
//				Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);
//				stateChange = false;
//			}else if(stateChange && !statusPing){
//				Firebase.removeStreamCallback(stream);
//				stateChange = false;
//			}

//			if (millis() - sendDataPrevMillis1 > 100){
//				digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//				sendDataPrevMillis1 = millis();
//			}
//
//			if (statusPing && (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))) {
//				Serial.println("<---------------------- Get Firebase ------------------------>");
//				delay(1000);
//				sendDataPrevMillis = millis();
//				count++;
//				FirebaseJson json;
//				json.add("data", "hello");
//				json.add("num", count);
//				Serial.printf("Set json... %s\n\n", Firebase.setJSON(fbdo, "/test/stream/data/json", json) ? "ok" : fbdo.errorReason().c_str());
//			}
//
//			if (dataChanged) {
//				dataChanged = false;
//				// When stream data is available, do anything here...
//			}
		}
	}

//	if(!getConnectionHealth()){
////		connectWifi(3);
//		// Ping default gateway
//		if((millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)){
//
//			sendDataPrevMillis = millis();
//
//			Serial.printf("\n\nPinging default gateway with IP %s\n", WiFi.gatewayIP().toString().c_str());
//			if(pinger.Ping(WiFi.gatewayIP()) == false){
//				Serial.println("Error during last ping command.");
//			}else{
//				Serial.println("Conexao ok!");
//				stationConnected = true;
//			}
//		}
//	}else{
////		if(startPing){
////			startPing = false;
////
////			pingOK();
////
////			Serial.print("Ping ok: ");
////			Serial.print((statusPing ? "true -> " : "false -> "));
////			Serial.println(contPing++);
////			Serial.print("stateChange ok: ");
////			Serial.println((stateChange ? "true -> " : "false -> "));
////		}
//
//		if(stateChange && statusPing){
//
//			if (!Firebase.beginStream(stream, "/test/stream/data")) {
//			  Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());
//			}
//
//			Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);
//			stateChange = false;
//		}else if(stateChange && !statusPing){
//			Firebase.removeStreamCallback(stream);
//			stateChange = false;
//		}
//
//		if (millis() - sendDataPrevMillis1 > 100){
//			digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//			sendDataPrevMillis1 = millis();
//		}
//
//		if (statusPing && (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))) {
//			Serial.println("<---------------------- Get Firebase ------------------------>");
//			delay(1000);
//			sendDataPrevMillis = millis();
//			count++;
//			FirebaseJson json;
//			json.add("data", "hello");
//			json.add("num", count);
//			Serial.printf("Set json... %s\n\n", Firebase.setJSON(fbdo, "/test/stream/data/json", json) ? "ok" : fbdo.errorReason().c_str());
//		}
//
//		if (dataChanged) {
//			dataChanged = false;
//			// When stream data is available, do anything here...
//		}
//	}
}

//bool pingOK(){
//	Serial.printf("\n\nPinging google ip 8.8.8.8\n");
//	return pinger.Ping(IPAddress(8,8,8,8), 1);
//}

//void timerInterrupt(){
////	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//
//	if(!--cont){
//	    cont = RELOAD_CONT;
//	    startPing = true;
//	}
//}
