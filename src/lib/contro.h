

void dbstatus()
{
       for (int i = 0; i < valdata.stbconec; i++)
    {
      valdata.datastausVal[i] = valdata.datastaus[i];
    }
}
void updatestaus(int datain, int id)
{
       for (int i = 0; i < valdata.stbconec; i++)
    {
     if (id== valdata.ID[i].toInt())
      {
                    valdata.datastausVal[i] = datain;
                   
      }
    }
}
bool traingcontro(String data, int sensor,int iddv)
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
     delay(2);

     if (lisdata[4] == "1")
     {
          
          if (lisdata[1] == "=")
          {
               

               if (datasen == sensor)
               {    
                    //Serial.println(lisdata[2].toInt());
                    updatestaus(staus, lisdata[2].toInt());
                    return true;
               }
          }

          else if (lisdata[1] == ">")
          {

               if (sensor > datasen)
               {
                    //Serial.println(lisdata[2].toInt());
                    updatestaus(staus, lisdata[2].toInt());

                    return true;
               }
          }

          else if (lisdata[1] == "<")
          {

               if (sensor < datasen)
               {
                    //Serial.println(lisdata[2].toInt());
                   updatestaus(staus, lisdata[2].toInt());
                    return true;
               }
          }
     }

     return false;
}
