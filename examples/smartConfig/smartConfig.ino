#include <api.h>
Connec b;
mqt s;
String ssid = "";
String password = "";
String AccessKey = "xxxx"; 
void setup()
{
  Serial.begin(115200);
   b.configpin(16);
  b.beginsmartconfig(AccessKey,0);
 
  

}
void loop()
{
  b.timeoutmqtt();
 }