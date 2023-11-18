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
	Serial.println();

	Serial.printf("Received stream payload size: %d (Max. %d)\n\n", data.payloadLength(), data.maxPayloadLength());

	dataChanged = true;
}

void streamTimeoutCallback(bool timeout) {
	if (!stream.httpConnected())
	  Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());

	if (timeout) {
		Serial.println("stream timed out, resuming...\n");
		removeStreamCallback();
	}
}

void beginStreamCallback(){
	Serial.println("-------------- beginStreamCallback ------------");

	if (!Firebase.beginStream(stream, "/test/stream/data")) {
	  Serial.printf("stream begin error, %s\n\n", stream.errorReason().c_str());
	}else{
		Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);
	}
}

void removeStreamCallback(){
	Serial.println("-------------- removeStreamCallback ------------");

	Firebase.removeStreamCallback(stream);
	setConnectionHealth(false);
}


void firebaseConfiguration(){

	Serial.println("-------------- firebaseConfiguration ------------");

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

	Firebase.reconnectWiFi(true);

	#if defined(ESP8266)
		stream.setBSSLBufferSize(2048 /* Rx in bytes, 512 - 16384 */, 512 /* Tx in bytes, 512 - 16384 */);
	#endif
}

//TODO - Remover
unsigned long sendDataPrevMillis = 0;
int count = 0;

void fhadskjlfa(){
	if (getConnectionHealth() && (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))) {
		Serial.println("<---------------------- Get Firebase ------------------------>");
		delay(1000);
		sendDataPrevMillis = millis();
		count++;
		FirebaseJson json;
		json.add("data", "hello");
		json.add("num", count);
		Serial.printf("Set json... %s\n\n", Firebase.setJSON(fbdo, "/test/stream/data/json", json) ? "ok" : fbdo.errorReason().c_str());
	}

	if (dataChanged) {
		dataChanged = false;
		// When stream data is available, do anything here...
	}
}
