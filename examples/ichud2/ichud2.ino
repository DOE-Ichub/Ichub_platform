String mm="";
#include "api.h"

Connec  b;
mqt s;
 String  ssid="";
 String password="";
String  AccessKey = "OMTM39";
void setup() {
  Serial.begin(115200);
 mySwitch.enableReceive(D6); 
  b.beginwifi(ssid,password,AccessKey);
}
void loop() { 
b.timeoutmqtt();
} 
