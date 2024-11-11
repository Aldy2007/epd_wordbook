#include "wordbook.h"
#include "../global.h"
#define API "http://172.28.1.10:8888"//替换为自己的服务器
#define SPACE 5
#define WORD false
#define MEANING true
#define WORD_Y 30
#define MEANING_Y 80
extern UBYTE *BlackImage;
extern bool Wifi_Status;

void paint_sent(int x0, int y0, bool type) {
    Serial.println("requestAPI+WORD");
    String res = request(API + String("/word"));
    Serial.println("res===");
    Serial.println(res);
    JsonDocument doc;
    deserializeJson(doc, res);
    int x = x0, y = y0;
    int len = (type == WORD) ? doc["font_word"].size() : doc["font_meaning"].size();
    Serial.print("len=");
    Serial.println(len);
    for (int i = 0; i < len; i++) {

        // 处理 uniurl 赋值
        String uniurl;
        if (type == WORD) {
            uniurl = String(doc["font_word"][i].as<const char *>()); // 确保正确转换类型
        } else {
            uniurl = String(doc["font_meaning"][i].as<const char *>()); // 确保正确转换类型
        }

        // 拼接 API 和 Unicode 参数
        uniurl = String(API) + "/char?unicode=" + uniurl;
        Serial.println(uniurl);
        Serial.print("URIRUIRUI");

        // 发送 HTTP 请求并接收响应
        String hex_string = request(uniurl.c_str()); // 使用 c_str() 确保正确处理

        // 绘制字符
        paint_char(x, y, hex_string);

        // 更新 x 坐标
        x += 6 + SPACE;
        if (x >= EPD_2in13_V4_HEIGHT) {
            Serial.println("X>=HEIGHT");
            y += get_char_height(hex_string);
            Serial.println(y);
            x = x0;
            if (y >= MEANING_Y && type == WORD) {
                Serial.print("Out of range (WORD)");
                return;
            }
            if (y >= EPD_2in13_V4_WIDTH) {
                Serial.print("Out of range (TOTAL)");
                return;
            }
        }
    }
}
void wordbook(int T) {}

void pre_word(int T) {}

void nxt_word(int T) {
    // Paint_ClearWindows(30, 20, 250, 120, WHITE);
    paint_sent(50, WORD_Y, WORD);       // 单词
    paint_sent(50, MEANING_Y, MEANING); // 意思
    EPD_2in13_V4_Display_Partial(BlackImage);
}
