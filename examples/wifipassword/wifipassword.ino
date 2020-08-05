
#include "api.h"

Connec b;
mqt s;
String ssid = "";
String password = "";
String AccessKey = "xxxxx"; // lấy key trên app ichub
void setup()
{
  Serial.begin(115200);
  b.beginwifi(ssid, password, AccessKey);
}
void loop()
{
  b.timeoutmqtt();
}
