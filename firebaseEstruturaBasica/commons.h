#ifndef COMMONS_H_
#define COMMONS_H_

#include "Arduino.h"
//#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

extern "C"
{
  #include <lwip/icmp.h> // needed for icmp packet definitions
}

#endif /* COMMONS_H_ */
