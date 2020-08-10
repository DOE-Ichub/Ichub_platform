

void set(int pinpwm)
{

#if defined(ESP32)
      Serial.println(" CONNECTED MQTT");
      analogWriteResolution (pinpwm, 12 );
#endif
 
}
  
void beginpinrelay()
{
  for (int i = 0; i < valdata.stbconec; i++)
  {
    String vt = valdata.VT[i];

    for (int j = 1; j <= valdata.sloutput; j++)
    {
      if (vt[j - 1] == '1')
      {

        if (valdata.TYPE[i] == 1 || valdata.TYPE[i] == 4)
        {

          delay(10);
          switch (j)

          {
          case 1:
          {
            pinMode(outputpin.digital[0], OUTPUT);
            digitalWrite(outputpin.digital[1], LOW);
          }
          break;
          case 2:
          {
            pinMode(outputpin.digital[1], OUTPUT);
            digitalWrite(outputpin.digital[1], LOW);
          }
          break;
          case 3:
          {
            pinMode(outputpin.digital[2], OUTPUT);
            digitalWrite(outputpin.digital[2], LOW);
          }
          break;
          case 4:
          {
            pinMode(outputpin.digital[3], OUTPUT);
            digitalWrite(outputpin.digital[3], LOW);
          }
          break;
          case 5:
          {
            pinMode(outputpin.digital[4], OUTPUT);
            digitalWrite(outputpin.digital[4], LOW);
          }
          break;
          case 6:
          {
            pinMode(outputpin.digital[5], OUTPUT);
            digitalWrite(outputpin.digital[5], LOW);
          }
          break;
          }
        }
        if (valdata.TYPE[i] == 3)
        {

          switch (j)

          {
          case 1:
          {
            pinMode(outputpin.analog[0], OUTPUT);

            analogWrite(outputpin.analog[0], 0);
          }
          break;
          case 2:
          {
            pinMode(outputpin.analog[1], OUTPUT);

            analogWrite(outputpin.analog[1], 0);
          }
          break;
          case 3:
          {
            pinMode(outputpin.analog[2], OUTPUT);
            analogWrite(outputpin.analog[2], 0);
          }
          break;
          case 4:
          {
            pinMode(outputpin.analog[3], OUTPUT);
            analogWrite(outputpin.analog[3], 0);
          }
          break;
          case 5:
          {
            pinMode(outputpin.analog[4], OUTPUT);
            analogWrite(outputpin.analog[4], 0);
          }
          break;
          case 6:
          {
            pinMode(outputpin.analog[5], OUTPUT);
            analogWrite(outputpin.analog[5], 0);
          }
          break;
          }
        }
      }
    }
  }
}
void onoffpinrelay(int vt, uint8_t stt)
{

  switch (vt)
  {
  case 1:
  {

    digitalWrite(outputpin.digital[0], stt);
    delay(10);
  }
  break;
  case 2:
  {
    digitalWrite(outputpin.digital[1], stt);
    delay(10);
  }
  break;
  case 3:
  {
    digitalWrite(outputpin.digital[2], stt);
    delay(10);
  }
  break;
  case 4:
  {

    digitalWrite(outputpin.digital[3], stt);
    delay(10);
  }
  break;
  case 5:
  {

    digitalWrite(outputpin.digital[4], stt);
    delay(10);
  }
  break;
  case 6:
  {

    digitalWrite(outputpin.digital[5], stt);
    delay(10);
  }
  break;
  }
}
void onoffpinpwm(int vt, int stt)
{

  switch (vt)
  {
  case 1:
  {

    analogWrite(outputpin.analog[0], stt);
  }
  break;
  case 2:
  {
    
    analogWrite(outputpin.analog[1], stt);
  }
  break;
  case 3:
  {
    
    analogWrite(outputpin.analog[2], stt);
  }
  break;
  case 4:
  {

    analogWrite(outputpin.analog[3], stt);
  }
  break;
  case 5:
  {

    analogWrite(outputpin.analog[4], stt);
  }
  break;
  case 6:
  {

    analogWrite(outputpin.analog[5], stt);
  }
  break;
  }
}

void dktb(int i, int dataof)
{
}

bool deriver(int dataof, int i, int idnut)
{
  int dimerpw = 0;
  if (valdata.ID[i].toInt() == idnut)
  {

    if (valdata.TYPE[i] == 1 || valdata.TYPE[i] == 4)
    {

      String vt = valdata.VT[i];
      for (int j = 1; j <= valdata.sloutput; j++)
      {
        if (vt[j - 1] == '1')
        {

          valdata.datastaus[i] = dataof;
          onoffpinrelay(j, dataof);
        }
      }

      return true;
    }

    else if (valdata.TYPE[i] == 3)
    {
      dimerpw = (dataof * outputpin.valpwm);
      String vt = valdata.VT[i];
      for (int j = 1; j <= valdata.sloutput; j++)
      {
        if (vt[j - 1] == '1')
        {

          valdata.datastaus[i] = dataof;
          onoffpinpwm(j, dimerpw);
        }
      }

      return true;
    }
  }
}
bool anhxa(String data, int dataof)
{
  bool stt = false;
  int datas[4];
  String ds;
  int st = 0;
  int vti = 0;

  for (int i = 0; i < data.length(); i++)
  {
    if (data[i] != '|')
    {
      ds += data[i];
      if (st == 3)
        datas[st] = ds.toInt();
    }
    else if (data[i] == '|')
    {

      datas[st] = ds.toInt();
      ds = "";
      st++;
    }
  }
  delay(10);
  if (datas[3] == 1)
  {

    for (int i = 0; i < valdata.stbconec; i++)
    {
      if (valdata.ID[i].toInt() == datas[1])
        vti = i;
    }

    if (datas[0] == dataof)
    {

      stt = deriver(datas[2], vti, datas[1]);
    }
  }
  return stt;
}
bool onoff(int dataof, int idnut)
{
  bool stt = false;
  for (int i = 0; i < valdata.stbconec; i++)
  {
    if (valdata.ID[i].toInt() == idnut)
    {

      stt = deriver(dataof, i, idnut);
      String data;
      for (int j = 0; j < valdata.socaidat; j++)
      {
        data = valdata.setingdataanhxa[i][j];
        if (data.length() == 0)
          break;
        stt = anhxa(data, dataof);
      }
    }
  }
  return stt;
}
