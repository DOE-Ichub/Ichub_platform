int cfnut = 13;
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
void ngat()
{

  int pp = 0;
  while (digitalRead(cfnut) == LOW)
  {
    delay(200);
    Serial.println(pp);
    pp++;
    if (digitalRead(cfnut) == LOW)
      if (pp >= 15)
      {
        break;
      }
  }
  if (pp >= 15)
  {

    wf.stwifi = false;

    EEPROM.put(0, wf);
    EEPROM.commit();
    delay(500);
    ESP.restart();
  }

  pp = 0;
}

void setup_wifi()
{
  String o = "";
  delay(10);

  WiFi.begin((wf.ssd).c_str(), (wf.pass).c_str());
}
bool wificonf(String sd, String pas)
{
  pinMode(16, OUTPUT);
   urlgetmqtt= urlgetmqtt+"/GetInfoServer";
  EEPROM.begin(1000);
  int cnt = 0;
  int i = 0;
  pinMode(cfnut, INPUT);

  if (sd.length() > 0)
  {
    wf.ssd = sd;
    wf.pass = pas;
    wf.stwifi = true;
  }
  else
  {
    if (EEPROM.read(0) == false || EEPROM.read(0) == true)
    {
      EEPROM.get(0, wf);
    }
    else
    {

      wf.ssd = "";
      wf.pass = "";
      wf.stwifi = false;
    }
  }

  WiFi.mode(WIFI_STA);
  if (wf.stwifi)
  {
    setup_wifi();
    while (WiFi.status() != WL_CONNECTED)
    {

      ngat();
      i++;
      digitalWrite(16, HIGH);

      delay(400);
      digitalWrite(16, LOW);
      delay(100);

      if (i > 10)
      {
        setup_wifi();
        i = 0;
        delay(1000);
      }
    }
    digitalWrite(16, HIGH);
    delay(500);
    return true;
  }

  while (!wf.stwifi)
  {

    WiFi.beginSmartConfig();
    while (WiFi.status() != WL_CONNECTED)
    {
      digitalWrite(16, HIGH);

      delay(200);
      digitalWrite(16, LOW);
      if (WiFi.smartConfigDone())
      {
        digitalWrite(16, HIGH);
      }
      delay(200);

      ngat();
    }

    delay(50);

    wf.ssd = WiFi.SSID();
    wf.pass = WiFi.psk();

    wf.stwifi = true;

    EEPROM.put(0, wf);
    EEPROM.commit();
    delay(10);
    Serial.println(wf.stwifi);
    Serial.println(EEPROM.read(0));
    Serial.println(EEPROM.read(1));
    Serial.println(EEPROM.read(2));
    Serial.println(EEPROM.read(3));
    delay(5000);

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
