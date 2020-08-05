
bool traingcontro(String data, int sensor)
{
     int datas[5];
     String ds;
     String lisdata[5];  
     int st = 0;
     int datasen = 0;
     int staus = 0;
     for (int i = 0; i < data.length(); i++)
     {
          if (data[i] != '|')
          {
               ds += data[i];

               if (st == 4)
                    lisdata[4] = ds;
          }
          else if (data[i] == '|')
          {
              
               lisdata[st] = ds;
               ds = "";
               st++;
          }
     }
     datasen = lisdata[0].toInt();
     staus = lisdata[3].toInt();
     delay(200);

     if (lisdata[4] == "1")
     {

          if (lisdata[1] == "=")
          {
               Serial.println("con tro vao =");

               if (datasen == sensor)
               {    

                    onoff(staus, lisdata[2].toInt());

                    return true;
               }
          }

          else if (lisdata[1] == ">")
          {

               if (sensor > datasen)
               {

                    onoff(staus, lisdata[2].toInt());

                    return true;
               }
          }

          else if (lisdata[1] == "<")
          {

               if (sensor < datasen)
               {

                    onoff(staus, lisdata[2].toInt());

                    return true;
               }
          }
     }

     return false;
}
