#ifndef conmqtt_h
#define conmqtt_h

#include <Arduino.h>

class mqt
{
public:
  void connectToMqtt(String url, String use, String pas);
  void sesor(int i, String datain);
  void loopmqt();
  void beginsever(String url, String m, String key, String mac);
  bool Writepin(int id, int stt);
  bool m(String id);
  int statusid(int idnut);

private:
  String key = "";
  
};
#endif
