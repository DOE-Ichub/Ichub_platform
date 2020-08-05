#ifndef api_h
#define api_h

#include <Arduino.h>
#if ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#include "HTTPClient.h"
#endif
#include "lib/ArduinoJson.h"
#include "conmqtt.h"

class Connec
{
public:
  void beginwifi(String ssid, String pass, String AccessKey);
  void beginwifi(String AccessKey);
  void timeoutmqtt();

private:
  int statusapi = 1;
  int mun = 0;
};

#endif
