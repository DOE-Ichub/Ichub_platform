# ICHUB PLATFORM
- Chúng tôi cung cấp nền tảng kết nối truyền thông đám mây miễn phí cho các thiết bị IoT nhầm mục đích nghiên cứu, học tập.
- Dowload: 
 [<img src="https://svgsilh.com/svg/1873373.svg" width="18" height="18" /> Website](http://ichub.doe.vn/huong-dan) | 
 [<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/googleplay.svg" width="18" height="18" /> Google Play](https://play.google.com/store/apps/details?id=com.ichub&hl=vi) | 
[<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/apple.svg" width="18" height="18" /> App Store](https://apps.apple.com/us/app/id1525228000)
# SỬ DỤNG

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
# SƠ ĐỒ CHÂN OUTPUT
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/examples/Untitled.png" width="800" height="400" />
<img src="https://github.com/DOE-Ichub/ICHUB_IOT/blob/master/examples/5c3f395196a56afb33b4.png" width="800" height="400" />
