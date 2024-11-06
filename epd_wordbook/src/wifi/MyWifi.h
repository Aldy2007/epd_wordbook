#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <WiFi.h>

class MyWiFi {
  public:
    MyWiFi();

    static void configure(const char *ssid, const char *password,
                          IPAddress staticIP, IPAddress gateway,
                          IPAddress subnet, IPAddress dns1,
                          IPAddress dns2 = IPAddress());

    void connect();
    bool Myping(const char *url);
    void check(uint8_t *&BlackImage, bool &Wifi_Status);
    IPAddress getIP();

  private:
    static const char *ssid;
    static const char *password;
    static IPAddress staticIP;
    static IPAddress gateway;
    static IPAddress subnet;
    static IPAddress dns1;
    static IPAddress dns2;
    IPAddress myIP;
};
void search_wifi();
String request(String url);
#endif // MY_WIFI_H
