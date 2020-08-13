#include <BH1750.h>
#include <api.h>

Connec b;
mqt s;
BH1750 lightMeter;
String ssid = "";
String password = "";
String AccessKey = "xxxxxx"; // lấy key trên app ichub
unsigned long val = 0;
String Light()
{
   uint16_t lux = lightMeter.readLightLevel(); /// đọc thông số sensor
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  return String(lux); 
}
void setup()
{
  Serial.begin(115200);
  lightMeter.begin(); 
  b.beginwifi(ssid, password, AccessKey);
   
}
void loop()
{
  b.timeoutmqtt();
 if(((unsigned long)(millis()-val))>500) ///cứ 500 ms là vào lấy thông số sensor vào gửi thông số 1 lần lên sever
 { 
  s.sensorsent(68418,Light()); //////gửi thông số sensor lên sever.
  val = millis(); 
 }
}
