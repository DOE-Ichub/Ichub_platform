#include <api.h>
Connec b;
mqt s;
String AccessKey = "xxxxx"; // lấy key trên app ichub
void setup()
{
  Serial.begin(115200);
  b.begismartconfis(AccessKey,0);
}
void loop()
{
  b.timeoutmqtt();
}
