
#ifndef INTERRUPTION_H_
#define INTERRUPTION_H_

#include "Arduino.h"

#define RELOAD_CONT 5

//Declara constantes
const int BASE_TIME = 8000;
const int DIVISOR_TIMER = 256;

extern void reloadRegDelayPing();
extern void timer1Configuration();
extern bool getStartPing();
extern void setStartPing(bool value);
extern bool getFlgRegDelayPing();
extern void setFlgRegDelayPing(bool value);
extern bool getCheckHealthConnection();
extern void healthConnection();


#endif /* INTERRUPTION_H_ */
