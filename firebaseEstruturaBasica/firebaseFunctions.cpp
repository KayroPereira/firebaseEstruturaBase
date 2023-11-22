#include "firebaseFunctions.h"

// Define Firebase Data object
FirebaseData stream;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

volatile bool dataChanged = false;


void streamCallback(StreamData data) {
	Serial.printf("stream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\n\n",
				data.streamPath().c_str(),
				data.dataPath().c_str(),
				data.dataType().c_str(),
				data.eventType().c_str());
	printResult(data); // see addons/RTDBHelper.h

	Serial.printf("\n\nReceived stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());

	dataChanged = true;
}

void streamTimeoutCallback(bool timeout) {
	if(getConnectionHealth()){
		if (!stream.httpConnected())
		  Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());

		if (timeout) {
			println("stream timed out, resuming...\n");
			stopStreamCallback();
		}
	}
}

void starStreamCallback(){

	if (!Firebase.beginStream(stream, "/test/stream/data")) {
			Serial.printf("stream begin error, %s\n\n", stream.errorReason().c_str());
		}

		Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);

		delayMilliSeconds(2000);
}

void stopStreamCallback(){

	Firebase.removeStreamCallback(stream);

	delayMilliSeconds(2000);

	setConnectionHealth(false);
}


void firebaseConfiguration(){

	/* Assign the api key (required) */
	config.api_key = API_KEY;

	/* Assign the user sign in credentials */
	auth.user.email = USER_EMAIL;
	auth.user.password = USER_PASSWORD;

	/* Assign the RTDB URL (required) */
	config.database_url = DATABASE_URL;

	/* Assign the callback function for the long running token generation task */
	config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

	Firebase.begin(&config, &auth);

	//Timeout options.

	// Comment or pass false value when WiFi reconnection will control by your code or third party library
	Firebase.reconnectWiFi(true);

	//WiFi reconnect timeout (interval) in ms (10 sec - 5 min) when WiFi disconnected.
	config.timeout.wifiReconnect = 10 * 1000;

	//Socket connection and SSL handshake timeout in ms (1 sec - 1 min).
	config.timeout.socketConnection = 5 * 1000;

	//Server response read timeout in ms (1 sec - 1 min).
	config.timeout.serverResponse = 5 * 1000;

	//RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
	config.timeout.rtdbKeepAlive = 20 * 1000;

	//RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
	config.timeout.rtdbStreamReconnect = 1 * 1000;

	//RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
	//will return false (error) when it called repeatedly in loop.
	config.timeout.rtdbStreamError = 3 * 1000;

	//You can also set the TCP data sending retry with
	config.tcp_data_sending_retry = 1;

	#if defined(ESP8266)
		stream.setBSSLBufferSize(2048 /* Rx in bytes, 512 - 16384 */, 512 /* Tx in bytes, 512 - 16384 */);
	#endif

	starStreamCallback();
}

//TODO - Remover
unsigned long sendDataPrevMillis = 0;
int count = 0;

void sendDataFirebase(){
	bool firebaseOK = Firebase.ready();

	if(getConnectionHealth() && !firebaseOK){
		stopStreamCallback();
	}

	if (getConnectionHealth() && (firebaseOK && (getMillis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))) {

		println("<---------------------- Get Firebase ------------------------>");
		Serial.printf("token.uid: %s -> email: %s -> password: %s", auth.token.uid.c_str(), auth.user.email.c_str(), auth.user.password.c_str());

		delayMilliSeconds(1000);
		sendDataPrevMillis = getMillis();
		FirebaseJson json;
		json.add("data", "hello");
		json.add("num", ++count);


		if(!Firebase.setJSON(fbdo, "/test/stream/data/json", json)){
			stopStreamCallback();
			Serial.printf("\nSet json... %s\n\n", fbdo.errorReason().c_str());
		}else{
			Serial.printf("\nSet json... %s\n\n", "ok\n");
		}
	}

	if (dataChanged) {
		dataChanged = false;
		// When stream data is available, do anything here...
	}
}
