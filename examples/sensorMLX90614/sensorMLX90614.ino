#include <api.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Connec b;
mqt s;
String AccessKey = "KTFG82"; // lấy key trên app ichub
unsigned long val =0 ; 
void setup()
{
  Serial.begin(115200);
 
  b.beginsmartconfig(AccessKey,0);
   s.pinset(1,25,"analog");
  mlx.begin();
}
void loop()
{
  b.timeoutmqtt();
    if (((unsigned long)(millis() - val)) > 500)

  {
    String t1 = String(mlx.readAmbientTempC());
    String t2 = String(mlx.readObjectTempC());
     Serial.print("Ambient = "); Serial.print(t1); 
  Serial.print("*C\tObject = "); Serial.print(t2); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
          s.sensorsent(77112,t1);
          s.sensorsent(79380,t2);
          val = millis();
  }
}
