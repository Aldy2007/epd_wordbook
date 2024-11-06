#include "..\global.h"
extern UBYTE *BlackImage;
int digit2num(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    } else {
        return c - 'a' + 10;
    }
}

String hex201str(int num) {
    String s = "";
    for (int i = 1; i <= 4; i++) {
        if (num & 1) {
            s = "1" + s;
        } else {
            s = "0" + s;
        }
        num >>= 1;
    }
    return s;
}

int get_char_height(String hex_str){
    return hex_str.length()/6+4;
}
void paint_char(int x, int y, String hex_str) {
    int len = hex_str.length();
    uint8_t delta = 0;
    for (int i = 0; i < len; i += 6) {
        String dig = hex_str.substring(i, i + 5);
        Serial.println(dig);
        int num = 0;
        for (int j = 0; j <= dig.length() - 1; j++) {
            num = digit2num(dig[j]);
            String res = hex201str(num);
            for (int k = 0; k < res.length(); k++) {
                if (res[k] == '1') {
                    Paint_DrawPoint(x + delta, y, BLACK, DOT_PIXEL_1X1,
                                    DOT_FILL_AROUND);
                    delta++;
                } else {
                    delta++;
                }
            }
        }
        y++;
        delta = 0;
    }
}