#include "paintgui.h"
#include "../global.h"
extern UBYTE *BlackImage;

void Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int thickness) {
    if (thickness == 1) {
        Paint_DrawLine(x1, y1, x2, y2, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    } else {
        Paint_DrawLine(x1, y1, x2, y2, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    }
}
void Rec(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int thickness) {
    if (thickness == 1) {
        Paint_DrawRectangle(x1, y1, x2, y2, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    } else {
        Paint_DrawRectangle(x1, y1, x2, y2, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    }
}
void RecW(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int thickness) {
    if (thickness == 1) {
        Paint_DrawRectangle(x1, y1, x2, y2, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    } else {
        Paint_DrawRectangle(x1, y1, x2, y2, WHITE, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    }
}
void Refresh(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t x4, uint8_t y4) {
    RecW(x1, y1, x2, y2, 2);
    Rec(x1, y1, x2, y2, 1);
    Rec(x3, y3, x4, y4, 2);
}

void Server_Status_Refresh(int now) {
    switch (now) {
    case 1:
        Refresh(80, 80, 170, 100, 5, 30, 50, 50);
        Refresh(80, 50, 170, 70, 5, 30, 50, 50);
        break;
    case 2:
        Refresh(5, 30, 50, 50, 80, 50, 170, 70);
        Refresh(80, 80, 170, 100, 80, 50, 170, 70);
        break;
    case 3:
        Refresh(80, 50, 170, 70, 80, 80, 170, 100);
        Refresh(5, 30, 50, 50, 80, 80, 170, 100);
        break;
    }
    EPD_2in13_V4_Display_Partial(BlackImage);
}
void Server_Status_Init(int T) {
    Rec(5, 30, 50, 50, 2);
    Rec(80, 50, 170, 70, 1);
    Rec(80, 80, 170, 100, 1);

    Paint_DrawString_EN(100, 55, "OPEN", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(100, 85, "CLOSE", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(7, 35, "Back", &Font12, WHITE, BLACK);

    EPD_2in13_V4_Display_Partial(BlackImage);
}

void Start_Menu_Init(int T) {
    Paint_DrawString_EN(5, 40, "Server Status", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(5, 60, "Words", &Font12, WHITE, BLACK);
    Rec(3, 38, 100, 55, 2);
    Rec(3, 58, 45, 75, 1);
    EPD_2in13_V4_Display_Partial(BlackImage);
}

void Start_Menu_Refresh(int now) {
    switch (now) {
    case 1:
        Refresh(3, 58, 45, 75, 3, 38, 100, 55);
        break;
    case 2:
        Refresh(3, 38, 100, 55, 3, 58, 45, 75);
        break;
    }
    EPD_2in13_V4_Display_Partial(BlackImage);
}

void Word_Book_Init(int T) {
    Line(30, 20, 30, 122, 2);

    Rec(6, 25, 26, 38, 1);
    Line(9, 31, 23, 31, 1);
    Line(23, 31, 18, 27, 1);
    Line(23, 31, 18, 35, 1);

    Rec(6, 47, 26, 61, 1);
    Line(9, 53, 23, 53, 1);
    Line(9, 53, 14, 49, 1);
    Line(9, 53, 14, 57, 1);
    EPD_2in13_V4_Display_Partial(BlackImage);
}

void Word_Book_Refresh(int now) {
    switch (now) {
    case 1:
        Refresh(6, 47, 26, 61, 6, 25, 26, 38);
        break;
    case 2:
        Refresh(6, 25, 26, 38, 6, 47, 26, 61);
        break;
    }
    EPD_2in13_V4_Display_Partial(BlackImage);
}
void GUI_Init() {
    Line(0, 20, 250, 20, 2);

    Rec(3, 3, 25, 17,1);
    Rec(28, 3, 50, 17,1); 
    Rec(53, 3, 75, 17,1); 

    Line(8, 10, 20, 10, 1);
    Line(8, 10, 15, 7, 1);
    Line(8, 10, 15, 13, 1);

    Line(33, 10, 45, 10, 1);
    Line(45, 10, 38, 7, 1);
    Line(45, 10, 38, 13, 1);

    Line(58, 10, 65, 15, 1);
    Line(65, 15, 72, 5, 1);

    /*MENU*/

    Start_Menu_Init(0);

    EPD_2in13_V4_Display(BlackImage);
}

void Choose_Refresh(int now) {
    switch (now) {
    case 1:
        Refresh(53, 3, 75, 17, 3, 3, 25, 17);
        break;
    case 2:
        Refresh(3, 3, 25, 17, 28, 3, 50, 17);
        break;
    case 3:
        Refresh(28, 3, 50, 17, 53, 3, 75, 17);
        break;
    }
    EPD_2in13_V4_Display_Partial(BlackImage);
}