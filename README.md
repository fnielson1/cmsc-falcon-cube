# cmsc-falcon-cube
Christa McAuliffe Space Center Falcon cube

Change the settings in `lib/wifi_utils.cpp` to set this device's IP address.

```c++
/* Update the SSID, password, IP address, gateway, and subnet mask here */
const char ssid[] = "The_name_of_my_WiFi_network";
const char pass[] = "The_password_for_my_WiFi_network";
IPAddress localIP(192, 168, 2, 35); // 192.168.2.35
IPAddress gateway(192, 168, 2, 1);  // 192.168.2.1
IPAddress subnet(255, 255, 255, 0); // 255.255.255.0
```