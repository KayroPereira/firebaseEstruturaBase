
#ifndef _testWiFiPingV1_H_
#define _testWiFiPingV1_H_

//#include "commons.h"
#include "accessHardware.h"
//#include "connection.h"
//#include "PingUtils.h"

//#define RELOAD_CONT 100

//extern Pinger pinger;
extern bool stationConnected;
extern bool initializationOk;

void timerInterrupt();
bool pingOK();


extern void initializeHardware();
extern void connectWifi(int maximum_attempt);
extern void communicationBoot();
extern bool getConnectionHealth();
extern void setConnectionHealth(bool value);
extern void startCheckHealthConnection();

//firebaseFunctions
extern void sendDataFirebase();

#endif /* _testWiFiPingV1_H_ */
