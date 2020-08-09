#if ESP8266
struct
{
   int digital[6] = {14,15,12,5,4,13};
   int analog[6] =  {14,15,12,5,4,13};
   float valpwm = 10.22;

} outputpin;
#elif defined(ESP32)
struct
{
   int digital[6] = {14,15,18,5,4,13};
   int analog[6] =  {14,15,18,5,4,13};
   float valpwm = 2.5;

} outputpin;
#endif
unsigned long wet, wet1, wet2 = 0;
int rate = 2000;
int phutwet = 0;
String ramsen = "";
struct
{
  String sup1 = "";
  String sup2 = "";
  String pus1 = "";
  String pus2 = "";
  String clientId = "";
} variablemqtt;
struct
{
  bool stt = false;
  String ID[10];
  String VT[10];
  int TYPE[10];
  String UNIT[10];
  int datastaus[10] = {0, 0, 0, 0, 0};
  int stbconec = 0;
  int timereading[10] = {0, 0, 0, 0, 0};
  //String stringdata[10];
  String setingdata[10][10]; //////"[{{"giay|on-off|lap_lai|kich_hoat"}}
  String setingdataanhxa[10][10];
  String setingdatacontro[10][10];
  int socaidat = 10;
  int sloutput = 6;
} valdata;
