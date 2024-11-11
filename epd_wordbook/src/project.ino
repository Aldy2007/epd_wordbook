#include "global.h"

UBYTE *BlackImage;
UWORD Imagesize = (EPD_2in13_V4_WIDTH / 8 + 1) * EPD_2in13_V4_HEIGHT;

uint8_t Status = 1, nowj = 1, menu[10][10];
//       状态        子状态      菜单
typedef void (*Funcptr)(int);
Funcptr funcRefresh[10], func[10][10], funcinit[10];
//         刷新            功能            初始化

/*--------------WIFI CONFIG------------------------------*/
const char *ssid = "";
const char *password = "";
bool Wifi_Status = false;

IPAddress staticIP(172, 28, 1, 19);
IPAddress gateway(172, 28, 1, 154);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(114, 114, 114, 114);

void Wifi_Connect() {
    MyWiFi::configure(ssid, password, staticIP, gateway, subnet, dns);
    MyWiFi myWiFi;
    myWiFi.connect();
    // myWiFi.check(BlackImage, Wifi_Status);
}

/*----------------------------INIT--------------------------------*/
OneButton button(12);

void Init() {
    Serial.begin(115200);
    DEV_Module_Init();
    EPD_2in13_V4_Init();

    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        while (1)
            ;
    }

    Paint_NewImage(BlackImage, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 90, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    button.reset();
    button.attachClick(Click);
    button.attachLongPressStop(DoubleClick);
    button.setPressTicks(500);

    /*-----------主页面---------------*/
    menu[1][0] = 2;
    menu[1][1] = 2;
    menu[1][2] = 3;

    funcRefresh[1] = Start_Menu_Refresh;
    funcinit[1] = Start_Menu_Init;

    /*-----------状态---------------*/
    menu[2][1] = 1;
    menu[2][0] = 3;

    funcRefresh[2] = Server_Status_Refresh;
    funcinit[2] = Server_Status_Init;

    func[2][2] = open_server;
    func[2][3] = close_server;

    /*------------单词本------------*/
    menu[3][0] = 2;

    funcRefresh[3] = Word_Book_Refresh;
    funcinit[3] = Word_Book_Init;

    func[3][1] = nxt_word;
    func[3][2] = pre_word;
}

void DoubleClick() {
    switch (Choose) {
    case 1: // 左箭头
        nowj = (nowj == 1) ? menu[Status][0] : nowj - 1;
        funcRefresh[Status](nowj);
        Serial.print(Status);
        Serial.print("     ");
        Serial.print(nowj);
        break;

    case 2: // 右箭头
        nowj = (nowj % menu[Status][0]) + 1;
        funcRefresh[Status](nowj);
        Serial.print(Status);
        Serial.print("     ");
        Serial.print(nowj);
        break;

    case 3: // 确定
        if (menu[Status][nowj] != 0) {
            Status = menu[Status][nowj];
            Serial.print("Status = ");
            Serial.println(Status);
            Paint_ClearWindows(0, 21, 250, 120, WHITE);
            nowj = 1;
            funcinit[Status](0);
        } else {
            Serial.println("func~~");
            func[Status][nowj](0);
        }
        break;
    }
}
uint8_t Choose = 1;
void Click() {
    Choose = Choose % 3 + 1;
    Serial.print("refresh - ");
    Serial.println(Choose);
    Choose_Refresh(Choose);
}
void setup() {
    Init();
    GUI_Init();
    Wifi_Connect();
}
void loop() {
    delay(30);
    button.tick();
}
