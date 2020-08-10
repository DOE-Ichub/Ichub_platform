#include <api.h>
Connec b;
mqt s;

String AccessKey = "xxxx";
void setup()
{
  Serial.begin(115200);
  b.configpin(16);
  b.beginsmartconfig(AccessKey, 0);
}
void loop()
{
  b.timeoutmqtt();
}