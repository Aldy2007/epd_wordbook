#include "MyWiFi.h"
#include "../global.h"
#include <Arduino.h>
#include <HTTPClient.h>
#define API ""//替换为自己的服务器的页面
#define WIFI_TRY_TIMES 3

const char *MyWiFi::ssid = nullptr;
const char *MyWiFi::password = nullptr;
IPAddress MyWiFi::staticIP;
IPAddress MyWiFi::gateway;
IPAddress MyWiFi::subnet;
IPAddress MyWiFi::dns1;
IPAddress MyWiFi::dns2;

MyWiFi::MyWiFi() {}

void MyWiFi::configure(const char *ssid, const char *password,
                       IPAddress staticIP, IPAddress gateway, IPAddress subnet,
                       IPAddress dns1, IPAddress dns2) {
    MyWiFi::ssid = ssid;
    MyWiFi::password = password;
    MyWiFi::staticIP = staticIP;
    MyWiFi::gateway = gateway;
    MyWiFi::subnet = subnet;
    MyWiFi::dns1 = dns1;
    MyWiFi::dns2 = dns2;
}

void MyWiFi::connect() {
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    if (WiFi.config(staticIP, gateway, subnet, dns1, dns2) == false) {
        Serial.println("Configuration failed.");
    }
    int tryed_times = 0;
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED && tryed_times <= WIFI_TRY_TIMES) {
        delay(500);
        tryed_times++;
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connect Failed");
    } else {
        Serial.println("");
        Serial.println("WiFi connected");
        myIP = WiFi.localIP();
        Serial.println(myIP);
    }
}

bool MyWiFi::Myping(const char *url) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode >= 200 && httpCode < 300) { // 检查是否在成功响应代码范围内
        http.end();
        return true;
    }
    http.end();
    return false;
}
String request(String url) {
    Serial.print("Request:url=");
    Serial.println(url);
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode >= 200 && httpCode < 300) {
        String Res = http.getString();
        http.end();
        return Res;
    } else {
        Serial.println("Request Failed");
    }
    http.end();
}
void MyWiFi::check(uint8_t *&BlackImage, bool &Wifi_Status) {
    bool ret = MyWiFi::Myping("http://www.265.com/"); // 找到的一个http网站
    if (ret) {
        Serial.println("Ping http://www.265.com Success");
        // 检查 服务器状态
        if (Myping(API)) { 
            Paint_DrawString_EN(130, 1, "Online", &Font12, WHITE, BLACK);
            Wifi_Status = true;
        } else {
            Paint_DrawString_EN(130, 1, "Offline", &Font12, WHITE, BLACK);
            Wifi_Status = false;
        }
    } else {
        Paint_DrawString_EN(130, 1, "Disconnected", &Font12, WHITE, BLACK);
    }
    // 打印Wifi与服务器状态
    EPD_2in13_V4_Display_Partial(BlackImage);
}

IPAddress MyWiFi::getIP() { return myIP; }

void search_wifi() {
    // 初始化串口通信
    Serial.begin(115200);

    // 连接到 WiFi
    WiFi.mode(WIFI_STA); // 设置为 WiFi 客户端模式
    WiFi.disconnect();   // 断开任何已连接的网络
    delay(1000);

    // 开始扫描 WiFi 网络
    Serial.println("Scanning for WiFi networks...");

    int n = WiFi.scanNetworks(); // 执行扫描
    Serial.println("Scan done");

    if (n == 0) {
        Serial.println("No networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");

        for (int i = 0; i < n; i++) {
            // 输出网络名称和信号强度
            Serial.print("Network name: ");
            Serial.println(WiFi.SSID(i));
            Serial.print("Signal strength (dBm): ");
            Serial.println(WiFi.RSSI(i));
            Serial.println("-------------");

            // 输出是否加密
            if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
                Serial.println("Encryption: Open");
            } else {
                Serial.println("Encryption: Encrypted");
            }
        }
    }
}
