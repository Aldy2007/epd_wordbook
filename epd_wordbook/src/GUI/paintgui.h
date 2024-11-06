#ifndef PAINTGUI_H
#define PAINTGUI_H

#include "../global.h"

void GUI_Init();
void Choose_Refresh(int now);
void Start_Menu_Refresh(int now);
void Refresh(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t x3,uint8_t y3,uint8_t x4,uint8_t y4);
void Start_Menu_Init(int t);
void Server_Status_Init(int t);
void Server_Status_Refresh(int now);
void Word_Book_Init(int t);
void Word_Book_Refresh(int now);

#endif