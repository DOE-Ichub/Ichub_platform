String mm="";
#include "api.h"

Connec  b;
mqt s;
 String  ssid="";
 String password="";
String  AccessKey = "OMTM39";
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
static const uint8_t D6 = 12;
void setup() {
  Serial.begin(115200);
 mySwitch.enableReceive(D6); 
  b.beginwifi(ssid,password,AccessKey);

}

void loop() {
    if (mySwitch.available()) {
    unsigned long int mun = mySwitch.getReceivedValue();
    Serial.print("Received ");
    Serial.println( mun );
    mySwitch.resetAvailable();
    switch(mun)
    {
      case 5592332:
                    s.Writepin(37044,0);
                    break;
      case 5592368:
                    s.Writepin(37044,1);
                    break;
    }
  }
  
b.timeoutmqtt();
} 
