#ifndef IMPORTUTILS_H_
#define IMPORTUTILS_H_

//accessHardware
extern void serialInitialize(unsigned long baud);
extern void println(const char c[]);
extern void println(int num);
extern void print(const char c[]);
extern void delayMilliSeconds(unsigned long ms);
extern unsigned long getMillis();
extern bool getInitializationOk();
extern void setInitializationOk(bool value);
extern void pinWrite(uint8_t pin, uint8_t val);
extern int pinRead(uint8_t pin);
extern void setPin(uint8_t pin);
extern void clearPin(uint8_t pin);
extern void togglePin(uint8_t pin);

#endif /* IMPORTUTILS_H_ */
