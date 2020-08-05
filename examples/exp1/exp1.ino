#include <api.h>
Connec b;
mqt s;
String ssid = "";
String password = "";
String AccessKey = "HXGH21"; // lấy key trên app ichub
void setup()
{
  Serial.begin(115200);
  b.begismartconfis(AccessKey,0);
  Serial.println(s.pinset(1,12,"analog"));  /// set GPIO 12 làm chân analog;
  Serial.println(s.statusid(31752));    ////  lất tạng thái nút .
  s.Writepin(31752, 1);  // điều khiển nút lên mức 1 .
}
void loop()
{
  b.timeoutmqtt();
  
  delay(2000);
}
