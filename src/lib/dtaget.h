String timer(String data)
{
     int datas[4];
     String ds;
     int st = 0;
  
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

     return "{\"timer\":" + String(datas[0]) + ",\"swich\":" + String(datas[3]) + ",\"status\":" + String(datas[1])+ ",\"repeat\":" + String(datas[2]) +"}";
}
String contro(String data)
{
     int datas[4];
     String ds;
     int st = 0;

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

     return "{\"contro\":" + String(datas[0]) + ",\"compare\":" + String(datas[1]) + ",\"idcontro\":" + String(datas[2]*378) + ",\"status\":" + String(datas[3])  + ",\"swich\":" + String(datas[4]) +"}";
}