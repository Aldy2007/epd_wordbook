#include "server_status.h"
#include "../global.h"
#include <ArduinoJson.h>
#include <cstring>
extern UBYTE *BlackImage;
extern bool Wifi_Status;
void action(bool Open) {
    HTTPClient http;
    http.begin("");//这里是开机卡url
               
    int httpCode = http.GET();

    if (httpCode > 0) {
        String payload = http.getString();
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);
        Serial.println("Server_:");
        Serial.println(payload);
        const char *msg = doc["msg"];
        if (strcmp(msg, "OK")) {
            if (Open) {
                Paint_DrawString_EN(100, 30, "Opened", &Font12, WHITE, BLACK);
            } else {
                Paint_DrawString_EN(100, 30, "Closed", &Font12, WHITE, BLACK);
            }
            EPD_2in13_V4_Display_Partial(BlackImage);
        } else {
            Paint_DrawString_EN(100, 30, "Failed", &Font12, WHITE, BLACK);
            EPD_2in13_V4_Display_Partial(BlackImage);
        }
    } else {
        Serial.println("Error on HTTP request");
    }

    http.end();
}
void open_server(int T) { action(true); }
void close_server(int T) { action(true); }
