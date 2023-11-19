#ifndef ACCESSHARDWARE_H_
#define ACCESSHARDWARE_H_

#include "Arduino.h"
#include "PingUtils.h"
//#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define DELAY_TRY_COMMUNICATION			5000

//connection
extern void connectWifi();
extern bool pingOK();
extern void wifiInitialize();
extern bool getStationInitialized();
extern bool getStationConnected();

//accessHardware
void systemInformation();

extern void serialInitialize(unsigned long baud);
extern void println(const char c[]);
extern void println(int num);
extern void print(const char c[]);
extern void communicationBoot();
extern void initializeHardware();
extern void connectWifi(int maximum_attempt);
extern void startCheckHealthConnection();
extern void healthConnection();
extern void delayMilliSeconds(unsigned long ms);
extern void pinConfiguration(uint8_t pin, uint8_t mode);
extern unsigned long getMillis();
extern bool getConnectionHealth();
extern void setConnectionHealth(bool value);
extern bool getCheckHealthConnection();
extern void setCheckHealthConnection(bool value);
extern bool getInitializationOk();
extern void setInitializationOk(bool value);
extern void pinWrite(uint8_t pin, uint8_t val);
extern int pinRead(uint8_t pin);
extern void setPin(uint8_t pin);
extern void clearPin(uint8_t pin);
extern void togglePin(uint8_t pin);

//interruption
extern void reloadRegDelayPing();
extern void timer1Configuration();
extern void setStartPing(bool value);
extern bool getStartPing();
extern bool getFlgRegDelayPing();
extern void setFlgRegDelayPing(bool value);

//firebaseFunction
extern bool getPingBusy();
extern bool getStatusPing();
extern bool getStateChange();
extern void setStateChange(bool value);
extern void starStreamCallback();
extern void firebaseConfiguration();


#endif /* ACCESSHARDWARE_H_ */
