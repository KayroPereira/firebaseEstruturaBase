#ifndef PINGUTILS_H_
#define PINGUTILS_H_

#include <Pinger.h>

extern Pinger pinger;
extern bool statusPing;
extern bool stateChange;

void pingerReceive();
void pingerEnd();


//PingUtils
extern void setPingBusy(bool value);
extern bool getPingBusy();

#endif /* PINGUTILS_H_ */
