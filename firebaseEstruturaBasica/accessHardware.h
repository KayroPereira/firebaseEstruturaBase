#ifndef ACCESSHARDWARE_H_
#define ACCESSHARDWARE_H_

#include "Arduino.h"
#include "PingUtils.h"
//#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>

//// Provide the token generation process info.
//#include <addons/TokenHelper.h>
//
//// Provide the RTDB payload printing info and other helper functions.
//#include <addons/RTDBHelper.h>

//extern "C"
//{
//  #include <lwip/icmp.h> // needed for icmp packet definitions
//}

extern bool stationInitialized;
extern bool stationConnected;
extern bool initializationOk;

extern void communicationBoot();
extern void initializeHardware();
extern void connectWifi();
extern void connectWifi(int maximum_attempt);
extern bool getConnectionHealth();
extern void setConnectionHealth(bool value);
extern void reloadRegDelayPing();
extern void timer1Configuration();
extern void setStartPing(bool value);
extern bool getStartPing();
extern bool getCheckHealthConnection();
extern void setCheckHealthConnection(bool value);
extern bool getFlgRegDelayPing();
extern void setFlgRegDelayPing(bool value);
extern bool pingOK();
extern void startCheckHealthConnection();

//firebaseFunction
extern void firebaseConfiguration();
extern void beginStreamCallback();
//extern void removeStreamCallback();

void healthConnection();

extern void wifiInitialize();

////Declara constantes
//const int BASE_TIME = 8000;
//const int DIVISOR_TIMER = 256;


#endif /* ACCESSHARDWARE_H_ */
