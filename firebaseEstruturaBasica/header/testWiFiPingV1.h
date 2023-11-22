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
extern void setFlgsAccessHardware(unsigned int value);

//firebaseFunctions
extern void sendDataFirebase();

//pingUtils
extern void setFlgsPingUtils(unsigned int value);

//connection
extern void setFlgsConnection(unsigned int value);

//interruption
extern void setFlgsInterruption(unsigned int value);

#endif /* _testWiFiPingV1_H_ */
