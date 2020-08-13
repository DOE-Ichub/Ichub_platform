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
  char ssd[32];
  char pass[62];

}wf;

 #if   defined(ESP8266)
   int erom = 1000;
   int beginerom = 1500;
#elif defined(ESP32)
      int erom = 1000;
      int beginerom = 1500;
  #endif
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
  WiFi.begin(wf.ssd, wf.pass);
 
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
      for(int i = erom; i <= (erom+sizeof(wf)) ; i++)
      {
          EEPROM.write (i,0);
      }
      EEPROM.commit();
      delay(500);
       #if   defined(ESP8266)
             WiFi.setAutoConnect(0);
              #endif
      ESP.restart();
    }

    pp = 0;
  }
}
void scan()
{
    if(WiFi.status() != WL_CONNECTED)
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
  EEPROM.begin(beginerom);
  int cnt = 0;
  int i = 0;
  if (sd.length() > 0)
  {
    cf.cfst = false;
     sd.toCharArray(wf.ssd, sd.length() + 1);
    pas.toCharArray( wf.pass,pas.length() + 1);
    wf.stwifi = true;
  }
  else
  {
      return false;
  }

  WiFi.mode(WIFI_STA);
  
  if (wf.stwifi)
  {
    Serial.println("WL_CONNECTING");
   
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
  EEPROM.begin(beginerom);
  int cnt = 0;
  int i = 0;
    
    if (EEPROM.read(erom) == false || EEPROM.read(erom) == true)
    {
      EEPROM.get(erom, wf);
       Serial.println(wf.ssd);
       Serial.println(wf.pass);
    }
    else
    {
      wf.stwifi = false;
    }
     
  WiFi.mode(WIFI_STA);
  if (wf.stwifi)
  {
    Serial.println("WL_CONNECTING");
     Serial.println(sizeof (wf));
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

    String ssdwf = WiFi.SSID();
    String passwf = WiFi.psk();
  ssdwf.toCharArray(wf.ssd, ssdwf.length() + 1);

  passwf.toCharArray( wf.pass,passwf.length() + 1);
    wf.stwifi = true;

    EEPROM.put(erom, wf);
    delay(10);
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
