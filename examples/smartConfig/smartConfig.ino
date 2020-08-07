#include <api.h>
Connec b;
mqt s;
String ssid = "";
String password = "";
String AccessKey = "HXGH21"; // lấy key trên app ichub
void setup()
{
  Serial.begin(115200);
   b.confispin(21);
  b.beginsmartconfig(AccessKey,19);
 
  

}
void loop()
{
  b.timeoutmqtt();
 }
