#include <WiFiUdp.h>
#include <NTPClient.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "vn.pool.ntp.org", 25200, 0);

void beginntp()
{
   timeClient.begin();
   timeClient.update();
}
void kolap(String data,int vti,int vtj)
{

  data.setCharAt(data.length()-1, '0');
  valdata.setingdata[vti][vtj] = data;

}

bool timer(String data, int idnut,int vti,int vtj)
{
  int datas[4];
  String ds ;
   int st=0;

    for(int i =0;i<data.length();i++)
            {
                if(data[i]!='|')
                {
                ds+=data[i];
                 if(st==3) datas[st] = ds.toInt();
                }
                else if(data[i]=='|')
                {
                  
                    datas[st] = ds.toInt();
                    ds="";
                  st++;
                }
                
            }
     int gio =  timeClient.getHours();
    int phut =  timeClient.getMinutes();
   
    int nowtong = gio*60*60+phut*60;
     delay(200);

   if(datas[3]==1)
   {
      switch ( datas[2])
           {
           
                           case 0: 
                           {
                             
                            if(nowtong==datas[0])
                                {
                               
                                     onoff(datas[1],idnut);
                                    
                                          kolap(data,vti,vtj);
                                     return true;
                               
                                }                  
                            

                             
                           }
                              break;
                           case 1: 
                           {
                                   if(nowtong==datas[0])
                                        {
                                       
                                            onoff(datas[1],idnut);
                                            
                                             return true;
                                         
                                   
                                        }       
                           
                             }
                            break;
           }
   }
           return false;
}

