#include <Arduino.h>
#include "conmqtt.h"
#include "bien.h"
#if ESP8266
#include <ESP8266WiFi.h>
#include "dktb.h"
#elif defined(ESP32)
#include <WiFi.h>
#include "lib/analogWrite.h"
#include "dktb.h"
#endif

#include "prog.h"
#include "contro.h"
#include "lib/PubSubClient.h"
#include "timedns.h"
WiFiClient espClient;
PubSubClient client(espClient);

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
    variablemqtt.clientId.toCharArray(bufid, variablemqtt.clientId.length() + 1);
    char useremqtt[30] = "";
    use.toCharArray(useremqtt, use.length() + 1);
    char pasemqtt[40] = "";
    pas.toCharArray(pasemqtt, pas.length() + 1);
    if (client.connect(bufid, useremqtt, pasemqtt))
    {
      char topsup[40] = "";
      variablemqtt.sup1.toCharArray(topsup, variablemqtt.sup1.length() + 1);
      client.subscribe(topsup);
      char topsup2[40] = "";
      variablemqtt.sup2.toCharArray(topsup2, variablemqtt.sup2.length() + 1);
      client.subscribe(topsup2);
      beginntp();
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
    sent(variablemqtt.pus1, str);
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
  char use[40] = "";
  qsid.toCharArray(use, qsid.length() + 1);
  char pas[40] = "";
  qpass.toCharArray(pas, qpass.length() + 1);
  WiFi.begin(use, pas);
}
void mqt::connectToMqtt(String url, String use, String pas)
{

  if (WiFi.status() == WL_CONNECTED)
  {

    bool ev = wifimqtt(use, pas);

    if (ev == false)
    {

      wifisever(url, use, pas);
    }
    else
    {
      /// Serial.println("Đã đang nhap   mqtt");
    }
  }
  else
  {

    delay(500);
    beginwifi();
  }
}
void sensoracstion(int data, int iddv)
{

  bool ret = false;
  String hctr = "";

  if (valdata.TYPE[iddv] == 2)
  {
    for (int j = 0; j < valdata.socaidat; j++)
    {
      hctr = valdata.setingdatacontro[iddv][j];
      if (hctr.length() == 0)
        break;
      ret = traingcontro(hctr, data);
    }
    if (ret == true)
    {
      sent(variablemqtt.pus1, senstr());
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
void mqt::sesor(int idnut, String datain)
{
  if (((unsigned long)(millis() - wet1)) > rate)

  {
    for (int i = 0; i < valdata.stbconec; i++)
    {
      if (valdata.TYPE[i] == 2 && (idnut / 378) == valdata.ID[i].toInt())
      {
        valdata.datastaus[i] = datain.toInt();
        delay(2);
        rate = valdata.timereading[i] / 2;
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

void mqt::loopmqt()
{
  String h;
  int idnut = 0;
  if (timeClient.getSeconds() != phutwet)
  {
    phutwet = timeClient.getSeconds();
    for (int i = 0; i < valdata.stbconec; i++)
    {
      idnut = valdata.ID[i].toInt();
      if (valdata.TYPE[i] == 1)
      {
        for (int j = 0; j < valdata.socaidat; j++)
        {
          h = valdata.setingdata[i][j];
          if (h.length() == 0)
            break;
          bool ret = timer(h, idnut, i, j);
          if (ret == true)
          {
            sent(variablemqtt.pus1, senstr());
          }
        }
      }
      if (valdata.TYPE[i] == 3)
      {
        for (int j = 0; j < valdata.socaidat; j++)
        {
          h = valdata.setingdata[i][j];
          if (h.length() == 0)
            break;
          bool ret = timer(h, idnut, i, j);
          if (ret == true)
          {
            sent(variablemqtt.pus1, senstr());
          }
        }
      }
    }
  }

  client.loop();
  delay(5);
}
