#ifndef _testWiFiPingV1_H_
#define _testWiFiPingV1_H_

#include "accessHardware.h"

//accessHardware
extern void serialInitialize(unsigned long baud);
extern void initializeHardware();
extern void communicationBoot();
extern void startCheckHealthConnection();
extern bool getConnectionHealth();
extern void setConnectionHealth(bool value);
extern bool getInitializationOk();

//firebaseFunctions
extern void sendDataFirebase();

#endif /* _testWiFiPingV1_H_ */
