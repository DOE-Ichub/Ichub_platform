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
unsigned long wet =  0;
unsigned long wet1[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
unsigned long wet2[2] = {0, 0};
int rate = 900;
int phutwet = 0;
String ramsen = "";
struct
{
  String sup1 = "";
  String sup2 = "";
  String pus1 = "";
  String pus2 = "";
  String clientId = "";
  String pussql = "datalog/";
} variablemqtt;
struct
{
  int eromst = 1100; 
} addeerrom;

struct
{
  
  bool eromkeyst = true;
  char id[10][10];
  int stVar[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
} variableerromst;

struct
{
  bool stt = false;
  bool sttmqtt = false;
  String ID[10];
  String VT[10];
  int TYPE[10];
  String UNIT[10];
  double datastaus[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
  
  int datastausVal[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
  int datasid[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
  bool sqlid[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
  double datasidsent[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
  bool Notif[10] = {0, 0, 0, 0, 0,0,0, 0, 0, 0};
  int stbconec = 0;
  int timereading[10] = {0, 0, 0, 0, 0};
  //String stringdata[10];
  String setingdata[10][10]; 
  String setingdataanhxa[10][10];
  String setingdatacontro[10][10];
  int socaidat = 10;
  int sloutput = 6;
} valdata;
