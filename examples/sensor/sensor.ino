#include <api.h>
Connec b;
mqt s;

String AccessKey = "KIPD68"; // lấy key trên app ichub
int sensortrig1 = 27;
int sensorecho1 = 26;
unsigned long val =0 ; 
String dokhoancach(int trig,int echo)
{
   unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    
    /* In kết quả ra Serial Monitor */
    Serial.print(distance);
    Serial.println("cm");
   
    return String(distance);
}
void setup()
{
  Serial.begin(115200);
  b.configpin(21);
  b.beginsmartconfig(AccessKey,19);
  pinMode(sensortrig1, OUTPUT);
  pinMode(sensorecho1, INPUT);
}
void loop()
{
  b.timeoutmqtt();
    if (((unsigned long)(millis() - val)) > 500)

  {
          s.sensorsent(54432,dokhoancach(sensortrig1,sensorecho1));
          val = millis();
  }
}
