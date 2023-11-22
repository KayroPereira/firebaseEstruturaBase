#ifndef PINGUTILS_H_
#define PINGUTILS_H_

#include <Pinger.h>

//pingUtils
extern Pinger pinger;

void pingerReceive();
void pingerEnd();

extern void setPingBusy(bool value);
extern bool getPingBusy();
extern bool getStatusPing();
extern void setStatusPing(bool value);
extern bool getStateChange();
extern void setStateChange(bool value);

#endif /* PINGUTILS_H_ */
