#include <Arduino.h>
#include "conmqtt.h"
#include "bien.h"
#if ESP8266
#include <ESP8266WiFi.h>
#include "dktb.h"
#elif defined(ESP32)
#include <WiFi.h>
#include "srcv/analogWrite.h"
#include "dktb.h"
#endif

#include "prog.h"
#include "contro.h"
#include "dtaget.h"
#include "srcv/PubSubClient.h"
#include "timedns.h"
WiFiClient espClient;
PubSubClient client(espClient);

bool mqt::pinset(int vtriout, int pinout, String cl)
{
  if (vtriout > 6 || vtriout < 0)
  {
    return false;
  }

  if (cl == "digital")
  {
    outputpin.digital[vtriout - 1] = pinout;
    return true;
  }
  else if (cl == "analog")
  {
    outputpin.analog[vtriout - 1] = pinout;
    return true;
  }
  else
  {
    return false;
  }
}
int mqt::statusid(int idnut)
{
  for (int i = 0; i < valdata.stbconec; i++)
  {

    if ((idnut / 378) == valdata.ID[i].toInt())
    {

      return valdata.datastaus[i];
    }
  }
}
bool sent(String topic, String me)
{
  char tops[40] = "";
  topic.toCharArray(tops, topic.length() + 1);
  delay(50);
  char sen[1000] = "";
  me.toCharArray(sen, me.length() + 1);
  client.publish(tops, sen);
}

bool wifimqtt(String use, String pas)
{
  if (!client.connected())
  {
    delay(100);
    char bufid[14] = "";
    use.toCharArray(bufid, use.length() + 1);
    char useremqtt[30] = "";
    use.toCharArray(useremqtt, use.length() + 1);
    char pasemqtt[40] = "";
    pas.toCharArray(pasemqtt, pas.length() + 1);
    //Serial.println(useremqtt);
    Serial.println("Connecting MQTT");
    if (client.connect(bufid, useremqtt, pasemqtt))
    {
      char topsup[40] = "";
      variablemqtt.sup1.toCharArray(topsup, variablemqtt.sup1.length() + 1);
      client.subscribe(topsup);
      char topsup2[40] = "";
      variablemqtt.sup2.toCharArray(topsup2, variablemqtt.sup2.length() + 1);
      client.subscribe(topsup2);
      beginntp();
      Serial.println(" CONNECTED MQTT");
      delay(500);
      return true;
    }
    else
    {
      return false;
    }
  }

  else
  {
    return true;
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{

  payload[length] = '\0';
  String me = (char *)payload;

  char top[40] = "";
  variablemqtt.sup1.toCharArray(top, variablemqtt.sup1.length() + 1);

  char topsup[40] = "";
  variablemqtt.sup2.toCharArray(topsup, variablemqtt.sup2.length() + 1);
   if (strcmp(topic, top) == 0)
  {

    String str = datasen(me);
        if (ramsen != str)
    {
      sent(variablemqtt.pus1, ramsen);
      ramsen = senstr();
    }
   
  }
  if (strcmp(topic, topsup) == 0)
  {

    setingtimer(me);
    sent(variablemqtt.pus2, me);
  }
}

void wifisever(String url, String use, String pas)
{
  char mqtt_server[30] = "";
  url.toCharArray(mqtt_server, url.length() + 1);
  char pasemqtt[20] = "";
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(500);
  wifimqtt(use, pas);
  delay(3000);
}
void mqt::beginsever(String url, String m, String k, String mac)
{
  key = k;
  variablemqtt.clientId = mac;
  variablemqtt.sup1 = k + "/app";
  variablemqtt.sup2 = k + "/updateapp";
  variablemqtt.pus1 = k + "/device";
  variablemqtt.pus2 = "updatedevice/" + k;
  char mqtt_server[30] = "";
  url.toCharArray(mqtt_server, url.length() + 1);
  char pasemqtt[20] = "";
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  onoffstring(m);
  beginpinrelay();
  delay(500);
}
void beginwifi()
{
  String qsid = WiFi.SSID();
  String qpass = WiFi.psk();
  Serial.println(WiFi.SSID());
  Serial.println(qsid);
  Serial.println(qpass);
  char use[40] = "";
  qsid.toCharArray(use, qsid.length() + 1);
  char pas[40] = "";
  qpass.toCharArray(pas, qpass.length() + 1);
  WiFi.begin(use, pas);
}
bool mqt::connectToMqtt(String url, String use, String pas)
{

  if (WiFi.status() == WL_CONNECTED)
  {

    bool ev = wifimqtt(use, pas);

    if (ev == false)
    {
      Serial.println(" NOT CONNECTED MQTT");
      wifisever(url, use, pas);
    }
    else
    {
    }
  }
  else
  {
  }
}
void sensoracstion(int data, int iddv)
{

  bool ret = false;
  String hctr = "";

  if (valdata.TYPE[iddv] == 2)
  {
    dbstatus();
    for (int j = 0; j < valdata.socaidat; j++)
    {
      hctr = valdata.setingdatacontro[iddv][j];
      if (hctr.length() == 0)
        break;
      ret = traingcontro(hctr, data, iddv);
    }
    for (int i = 0; i < valdata.stbconec; i++)
    {
      if (valdata.datastaus[i] != valdata.datastausVal[i] && valdata.TYPE[i] != 2)
      {
        valdata.datastaus[i] = valdata.datastausVal[i];
        onoff(valdata.datastausVal[i], valdata.ID[i].toInt());
      }
    }
  }
}
bool mqt::Writepin(int id, int stt)
{
  bool kt = false;

  if (((unsigned long)(millis() - wet2)) > 200)

  {
    for (int i = 0; i < valdata.stbconec; i++)
    {

      if ((id / 378) == valdata.ID[i].toInt())
      {
        kt = onoff(stt, id / 378);
        sent(variablemqtt.pus1, senstr());
        return kt;
      }
    }
    wet2 = millis();
  }
  return kt;
}
void mqt::sensorsent(int idnut, String datain)
{

  bool ret = false;
  if (((unsigned long)(millis() - wet1)) > rate)

  {
    for (int i = 0; i < valdata.stbconec; i++)
    {

      if (valdata.TYPE[i] == 2 && (idnut / 378) == valdata.ID[i].toInt())
      {
        valdata.datastaus[i] = datain.toInt();
       
        if (valdata.timereading[i] != 0)
        {
          rate = valdata.timereading[i];
        }
       
        sensoracstion(valdata.datastaus[i], i);
      }
    }
    if (ramsen != senstr())
    {
      sent(variablemqtt.pus1, ramsen);
      ramsen = senstr();
    }
    wet1 = millis();
  }
}
String mqt::sensorget(int idnut)
{
  String hctr = "[";
  ;
  for (int i = 0; i < valdata.stbconec; i++)
  {
    if (valdata.TYPE[i] == 2 && (idnut / 378) == valdata.ID[i].toInt())
    {
      String str;
      String dta;
      for (int j = 0; j < valdata.socaidat; j++)
      {
        dta = valdata.setingdatacontro[i][j];
        if (dta.length() == 0)
          break;

        if (j > 0)
        {
          str += ",";
        }
        str += contro(dta);
      }
      hctr += str;
    }
  }
  hctr += "]";
  return hctr;
}
String mqt::dataget(int idnut)
{
  String hctr = "[";

  for (int i = 0; i < valdata.stbconec; i++)
  {
    if (valdata.TYPE[i] != 2 && (idnut / 378) == valdata.ID[i].toInt())
    {
      String str;
      String dta;
      for (int j = 0; j < valdata.socaidat; j++)
      {
        dta = valdata.setingdata[i][j];

        if (dta.length() == 0)
          break;
        if (j > 0)
        {
          str += ",";
        }
        str += timer(dta);
      }
      hctr += str;
    }
  }
  hctr += "]";
  return hctr;
}
void mqt::loopmqt()
{
  String h;
  int idnut = 0;
  if (timeClient.getMinutes() != phutwet)
  {
    
    for (int i = 0; i < valdata.stbconec; i++)
    {
        bool ret = false;
      idnut = valdata.ID[i].toInt();
      if (valdata.TYPE[i] == 1 ||valdata.TYPE[i] == 3)
      {
      
        for (int j = 0; j < valdata.socaidat; j++)
        {

          h = valdata.setingdata[i][j];
          if (h.length() == 0)
            break;
          ret = timer(h, idnut, i, j);
         
        }
        if (ret == true)
        {
          sent(variablemqtt.pus1, senstr());
        }
      }

    }
    phutwet = timeClient.getMinutes();
  }

  client.loop();
}
