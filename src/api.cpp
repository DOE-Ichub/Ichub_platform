
#include <Arduino.h>
#include "api.h"
 #include "beginprog.h"

#include <timer.h>
Timer timer;
#define HTTPCLIENT_1_1_COMPATIBLE
HTTPClient http;
mqt  c;
String statusmac(String AccessKey,String mac)
{
       String D = "";
       while(AccessKey.length()==0){delay(500);Serial.print(" vui long nhap key ");}
       D =   "={\"AccessKey\":\""+AccessKey+"\",\"Mac\":\""+mac+"\"}";
  return D;
}
int apipaym(String key,String mac)
{
   String laydulieu;
 
   if (!http.begin((urlgetmqtt))) {
    
        }
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int kiemtraloi2 = http.POST(statusmac(key,mac));

        int demapi =0;
  while( kiemtraloi2<0)
      {
       if (!http.begin((urlgetmqtt))) {
    
        }
 http.addHeader("Content-Type","application/json");
         kiemtraloi2 = http.POST(statusmac(key,mac));
         
         delay(500);
         demapi++;
         if(demapi>3)
         {
          return  99;
         }
         
      }
  if(kiemtraloi2>0)
    {
    
    if(kiemtraloi2 == HTTP_CODE_OK) {
    String laydulieu = http.getString();
  Serial.println(laydulieu);
   DynamicJsonDocument doc(10000);
       DeserializationError error = deserializeJson(doc, laydulieu);
  if (error) {

    return 99 ;
  }
    int Status = doc["Status"];   
 String dataj = doc["Data"];
  
 Serial.println(dataj);
  DynamicJsonDocument doc2(10000);
       DeserializationError error2 = deserializeJson(doc2, dataj);
  if (error2) {
    return 99 ;
  }  
    String S= doc2["Server"]["ServerName"];
    String U = doc2["Server"]["UserName"];
    String P = doc2["Server"]["PassWord"];
    String D = doc2["Data"];
 mqtt_serverstr = S;
 useremq = U;
 pasemq = P;
  m=D;
 


   return  0; 
    }
    
    else  return  99;
    
  }
}
void loopCallback() {
   c.connectToMqtt(mqtt_serverstr,useremq,pasemq);
   c.loopmqt();
      ngat();
      timer.start();
}
void Connec::beginwifi(String ssid,String pass,String key)
{
 
   bool wfstt =  wificonf(ssid,pass);

  WiFi.printDiag(Serial);

  Serial.println(WiFi.localIP());
  String mac = macid();
//    if(wfstt == true){ delay(2000);ESP.reset();}
    delay(500);
    while(statusapi !=0)
  {
    statusapi=apipaym(key,mac);
    delay(1000);
      if(mun++>20){
        while(1);
      }
  }
  c.beginsever(mqtt_serverstr,m,key,mac);
  timer.setTimeout(100);
  timer.setCallback(loopCallback);
  timer.start();
   
}
void Connec::timeoutmqtt()
{
  
 timer.update();

}

