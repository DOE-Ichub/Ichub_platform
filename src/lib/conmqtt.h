#ifndef conmqtt_h
#define conmqtt_h

#include <Arduino.h>

class mqt
{
public:
  bool connectToMqtt(String url, String use, String pas);
  void sensorsent(int id, String datain);
  void loopmqt();
  void beginsever(String url, String m, String key, String mac);
  bool Writepin(int id, int stt);
  bool m(String id);
  bool pinset(int vtriout,int pinout,String cl);
  String dataget(int idnut);
  String sensorget(int idnut);
  bool saveid(int idnut,bool save);
  int statusid(int idnut);

private:
  String key = "";
  
};
#endif
