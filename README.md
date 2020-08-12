# ICHUB PLATFORM
- Chúng tôi cung cấp nền tảng kết nối truyền thông đám mây miễn phí cho các thiết bị IoT nhầm mục đích nghiên cứu, học tập.
- Dowload: 
 [<img src="https://svgsilh.com/svg/1873373.svg" width="18" height="18" /> Website](http://ichub.doe.vn/huong-dan) | 
 [<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/googleplay.svg" width="18" height="18" /> Google Play](https://play.google.com/store/apps/details?id=com.ichub&hl=vi) | 
[<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/apple.svg" width="18" height="18" /> App Store](https://apps.apple.com/us/app/id1525228000)
### SỬ DỤNG
```cpp
#include <api.h>

Connec b;
mqt s;
String ssid = "DOE";
String password = "12345678";
String AccessKey = "HXGH21";
void setup()
{
  Serial.begin(115200);
  b.beginwifi(ssid, password, AccessKey);
}
void loop()
{
  b.timeoutmqtt();
}
```
Sử dụng mã tương tự ở trên, bạn có thể nhập `String ssid =` tên wifi `String password =` password wifi . 
* `AccessKey` = HXGH21
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/src/prin/accessskey.png" width="300" height="200" />

```cpp
#include <api.h>
Connec b;
mqt s;
String AccessKey = "HXGH21"; // lấy key trên app ichub
void setup()
{
  Serial.begin(115200);
  b.configpin(16);
  b.beginsmartconfig(AccessKey,0);
}
void loop()
{
  b.timeoutmqtt();
}
```
Sử dụng mã tương tự ở trên ngoài ra còn khai báo chân xuất tín hiệu Led báo tạng thái kết nối 
* `b.configpin(16)` - Khai báo chân GPIO 16 làm Pinout Startus trạng thái wifi kết nối  
* `b.beginsmartconfig(AccessKey,0)` - Khai báo chân GPIO 0 làm Pin input đọc tín thiệu nút nhấn kéo lên mức cao.
* `AccessKey` = HXGH21
 <img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/src/prin/accessskey.png" width="300" height="200" />
   

### `Connec` class

* ` bool configpin(int GPIO);` - Khai báo chân GPIO làm Pinout Startus trạng thái wifi kết nối .

* `bool beginwifi(String ssid, String pass, String AccessKey)` - Kết nối wifi bằng pass cố định 

* `bool beginsmartconfig(String AccessKey,int cfnut)` - kết nối bằng smartconfig ( Cfnut GPIO đọc phím nhấn để kích hoạt chế độ smartconfig).


### `mqt` class

* `int statusid(int id)` - Lấy trạng thái nút .

* `bool pinset(int vtriout,int pinout,String cl)`-Hàm này giúp ánh xạ chân mặt định thành chân mình mong muốn .`vtriout` ị trí output trên app, `pinout` GPIO của  module esp8266 hoặc esp32 cần xuất tín hiệu điều khiển.
	`cl` "digital" đối với tin hiệu 0 -1 , ,"analog"  đối với tin hiệu PWM 0- 1023 exp: s.pinset(3,12,"digital");

*  `bool Writepin(int id, int stt)` - Điều khiển trạng thái nút onoff digital (0 -1 ), PWM (0-1024). 

* `bool sensorsent(int id, String datain)` - Gửi dữ liệu sensor lên app hiển thị

* `String dataget(int idnut)` - Lấy dự liệu setting nút.

* `String sensorget(int idnut)` - Lấy dữ liệu setting sensor

* `bool timeoutmqtt()` - chạy mqtt.

# SƠ ĐỒ CHÂN OUTPUT
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/examples/Untitled.png" width="800" height="400" />
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/examples/5c3f395196a56afb33b4.png" width="800" height="400" />
