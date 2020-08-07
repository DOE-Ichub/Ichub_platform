#ifndef conmqtt_h
#define conmqtt_h

#include <Arduino.h>

class mqt
{
public:
  bool connectToMqtt(String url, String use, String pas);
  void sesor(int id, String datain);
  void loopmqt();
  void beginsever(String url, String m, String key, String mac);
  bool Writepin(int id, int stt);
  bool m(String id);
  bool pinset(int vtriout,int pinout,String cl);
  String dataget(int idnut);
  String sesorget(int idnut);
  int statusid(int idnut);

private:
  String key = "";
  
};
#endif
