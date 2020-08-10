# ICHUB PLATFORM
- Chúng tôi cung cấp nền tảng kết nối truyền thông đám mây miễn phí cho các thiết bị IoT nhầm mục đích nghiên cứu, học tập.
<<<<<<< HEAD
- Dowload: [Document](http://ichub.doe.vn/huong-dan)
 [App Store](https://apps.apple.com/us/app/id1525228000)
 [Google Play](https://play.google.com/store/apps/details?id=com.ichub&hl=vi)

=======
- Dowload: 
 [<img src="https://svgsilh.com/svg/1873373.svg" width="18" height="18" /> Website](http://ichub.doe.vn/huong-dan) | 
 [<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/googleplay.svg" width="18" height="18" /> Google Play](https://play.google.com/store/apps/details?id=com.ichub&hl=vi) | 
[<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/apple.svg" width="18" height="18" /> App Store](https://apps.apple.com/us/app/id1525228000)
>>>>>>> 40b03d126102d88aa7f5fec34b2a58284a708084
# SỬ DỤNG
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
Sử dụng mã tương tự ở trên, bạn có thể nhập `ssid`  tên wifi `password` password wifi . 
* `AccessKey`  <img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/src/prin/accessskey.png" width="300" height="200" />
--------------------------------------------
```
#include <api.h>
Connec b;
mqt s;
String ssid = "";
String password = "";
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
````
Sử dụng mã tương tự ở trên ngoài ra còn khai báo chân xuất tín hiệu Led báo tạng thái kết nối 
* `bool confispin(int ledcf)` - Khai báo chân GPIO 16 làm Pinout Startus trạng thái wifi kết nối  `b.configpin(16)`
* `b.beginsmartconfig(AccessKey,0)` - `AccessKey`  <img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/src/prin/accessskey.png" width="300" height="200" />
   Khai báo chân GPIO 0 làm Pin input đọc tín thiệu nút nhấn kéo lên mức cao.

### `Connec` class
* `bool beginwifi(String ssid, String pass, String AccessKey)` - Kết nối wifi bằng pass cố định 

* `bool beginsmartconfig(String AccessKey,int cfnut)` - kết nối bằng smartconfig ( Cfnut GPIO đọc phím nhấn để kích hoạt chế độ smartconfig).




### `mqt` class

* `int statusid(int id)` - Lấy trạng thái nút .
 
*  `bool Writepin(int id, int stt)` - Điều khiển truạng thái nút.

* `bool sesor(int id, String datain)` - Gửi dữ liệu sensor lên app hiển thị

* `String dataget(int idnut)` - Lấy dự liệu setting nút.

* `String sesorget(int idnut)` - Lấy dữ liệu setting sensor
* `bool timeoutmqtt()` - chạy mqtt.

<<<<<<< HEAD
=======
1. Kết nối wifi bằng pass cố định.
- bool beginwifi(String ssid, String pass, String AccessKey);

2. kết nối bằng smartconfis:
- bool begismartconfis(String AccessKey,int cfnut).

 **chú thích**:
- AccessKey: key trên ứng dụng.
- Ssid: tên wifi.
- Pass: password wifi
- Cfnut: GPIO đọc phím nhấn để kích hoạt chế độ smartconfis.

3. Output - Input

- Khai báo chân Startus trạng thái wifi kết nối.
- bool confispin(int ledcf);
- ledcf : GPIO kết nối led báo trạng thái.
- Lấy trạng thái nút :
- int statusid(int id);
- id : id nút được tạo trên ứng dụng.
- Điều khiển nút: bool Writepin(int id, int stt);
- id : id nút được tạo trên ứng dụng.
- stt : onoff digital (0 -1 ), PWM (0-1024). 
- Gửi dữ liệu sensor lên app hiển thị.
- sesor(int id, String datain);
- id : id nút được tạo trên ứng dụng.
- datain : dự liệu sensor truyền vào.
>>>>>>> 40b03d126102d88aa7f5fec34b2a58284a708084
# SƠ ĐỒ CHÂN OUTPUT
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/examples/Untitled.png" width="800" height="400" />
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/examples/5c3f395196a56afb33b4.png" width="800" height="400" />
