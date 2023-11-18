
#ifndef CONNECTION_H_
#define CONNECTION_H_

//#include "commons.h"

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "PingUtils.h"


/* 1. Define the WiFi credentials */
#define WIFI_SSID "kWiFiMobile"
#define WIFI_PASSWORD "123456789"
// #define WIFI_SSID "NetWifi2"
// #define WIFI_PASSWORD "Pedepano21@@"

#define MAXIMUM_ATTEMPT_CONNECTION_DEFAULT			15

extern bool stationInitialized;
extern bool stationConnected;
extern Pinger pinger;

extern void wifiInitialize();
extern void connectWifi();
extern void connectWifi(int maximum_attempt);
extern bool pingOK();

//PingUtils
extern void setPingBusy(bool value);
extern bool getPingBusy();

#endif /* CONNECTION_H_ */
