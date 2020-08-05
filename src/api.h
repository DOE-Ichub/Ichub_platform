#ifndef api_h
#define api_h

#include <Arduino.h>
#if ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#endif
#include "lib/srcv/ArduinoJson.h"
#include "lib/conmqtt.h"

class Connec
{
public:
  bool beginwifi(String ssid, String pass, String AccessKey);
  bool begismartconfis(String AccessKey,int cfnut);
  void timeoutmqtt();
  bool confispin(int ledcf);

private:
  int statusapi = 1;
  int mun = 0;
};

#endif
