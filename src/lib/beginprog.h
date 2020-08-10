struct
{
  bool cfst = false;
  bool cfstled = false;
  int cfnut = 13;
  int cfled = 16;
}cf;
struct
{
  bool stwifi;
  String ssd;
  String pass;

} wf;
String useremq = "";
String pasemq = "";
String mqtt_serverstr = "";
int xacnhanTT = 0;
String m = "";
String urlgetmqtt = "http://ichub-api.doe.vn";
#include <EEPROM.h>
void setup_wifi()
{
  String o = "";
  delay(10);

  WiFi.begin((wf.ssd).c_str(), (wf.pass).c_str());
}
void ngat()
{
  if (cf.cfst == true)
  {
    int pp = 0;
   
    while (digitalRead(cf.cfnut) == LOW)
    {
      delay(200);

      pp++;
      if (digitalRead(cf.cfnut) == LOW)
        if (pp >= 15)
        {
          break;
        }
    }
    if (pp >= 15)
    {
      Serial.println("reset esp");
      wf.stwifi = false;

      EEPROM.put(1000, wf);
      EEPROM.commit();
      delay(500);
      ESP.restart();
    }

    pp = 0;
  }
   if (WiFi.status() != WL_CONNECTED&&wf.stwifi == true)
   {
     digitalWrite(cf.cfled, LOW);
     delay(50);
      digitalWrite(cf.cfled, HIGH);
      setup_wifi();
     
   }
  
}


bool wificonf(String sd,String pas)
{

  urlgetmqtt = urlgetmqtt + "/GetInfoServer";
  EEPROM.begin(1500);
  int cnt = 0;
  int i = 0;
  if (sd.length() > 0)
  {
    cf.cfst = false;
    wf.ssd = sd;
    wf.pass = pas;
    wf.stwifi = true;
  }
  else
  {
      return false;
  }

  WiFi.mode(WIFI_STA);
  if (wf.stwifi)
  {
    setup_wifi();
    while (WiFi.status() != WL_CONNECTED)
    {

     
      i++;
      digitalWrite(cf.cfled, HIGH);

      delay(400);
      digitalWrite(cf.cfled, LOW);
      delay(100);

      if (i > 10)
      {
        setup_wifi();
        i = 0;
        delay(1000);
      }
    }
    digitalWrite(cf.cfled, HIGH);
    delay(500);
    return true;
  }

}
bool wifismartconf()
{

   urlgetmqtt = urlgetmqtt + "/GetInfoServer";
  EEPROM.begin(1500);
  int cnt = 0;
  int i = 0;
    
    if (EEPROM.read(1000) == false || EEPROM.read(1000) == true)
    {
      EEPROM.get(1000, wf);
    }
    else
    {
      wf.ssd = "";
      wf.pass = "";
      wf.stwifi = false;
    }
     
  WiFi.mode(WIFI_STA);
  if (wf.stwifi)
  {
    setup_wifi();
    while (WiFi.status() != WL_CONNECTED)
    {

      ngat();
      i++;
      digitalWrite(cf.cfled, HIGH);

      delay(400);
      digitalWrite(cf.cfled, LOW);
      delay(100);

      if (i > 10)
      {
        setup_wifi();
        i = 0;
        delay(1000);
      }
    }
    digitalWrite(cf.cfled, HIGH);
    delay(500);
    return true;
  }

  while (!wf.stwifi)
  {
    Serial.println("smartConfig");
    WiFi.beginSmartConfig();
    while (WiFi.status() != WL_CONNECTED)
    {
       
      digitalWrite(cf.cfled, HIGH);

      delay(200);
      digitalWrite(cf.cfled, LOW);
      if (WiFi.smartConfigDone())
      {
        digitalWrite(cf.cfled, HIGH);
      }
      delay(200);
    if (i > 200)
      {
        WiFi.beginSmartConfig();
        i = 0;
      }
      ngat();
    }

    delay(50);

    wf.ssd = WiFi.SSID();
    wf.pass = WiFi.psk();

    wf.stwifi = true;

    EEPROM.put(1000, wf);
    EEPROM.commit();
    delay(10);

    return true;
  }
}
String macid()
{
  String o = "";
  byte mac[6];
  delay(10);
  WiFi.macAddress(mac);
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x%02x%02x%02x%02x%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
