/**
 * @file HelloWorld.ino
 * @author HalfSweet (Email:HalfSweet@HalfSweet.cn or QQ:2522182733)
 * @brief 该文件为支持三色的墨水屏显示出三种颜色的例程
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>
#include <EPaperDrive.h>
//包含你需要使用的文件系统,例如：
#include <LittleFS.h>

#define BAUD_SPEED 74880 //串口调试的波特率，可自行修改

#define CS 15
#define RST 2
#define DC 0
#define BUSY 4
#define CLK 14
#define DIN 13
EPaperDrive EPD(0, CS, RST, DC, BUSY, CLK, DIN); //驱动库的实例化，此处为使用软件SPI

const uint8_t city_icon[24] = {
    /* 0X01,0X01,0X0C,0X00,0X0C,0X00, */
    0X00,
    0X00,
    0X1C,
    0X00,
    0X77,
    0X00,
    0X41,
    0X80,
    0X9C,
    0X60,
    0XA2,
    0X30,
    0XA2,
    0X30,
    0X9C,
    0XC0,
    0X41,
    0X80,
    0X77,
    0X00,
    0X1C,
    0X00,
    0X00,
    0X00,
};

void setup()
{
    Serial.begin(BAUD_SPEED);
    LittleFS.begin();     //请务必先手动初始化一遍文件系统再将指针传入
    EPD.SetFS(&LittleFS); //设置存放字体的文件系统，传入的为该文件系统的操作指针，可自行修改

    EPD.EPD_Set_Model(DKE42_3COLOR);                    //设置屏幕类型，具体型号可以参考文档
    EPD.EPD_init_Full();                                //全刷初始化，使用全刷波形
    EPD.clearbuffer();                                  //清空缓存(全白)
    EPD.fontscale = 2;                                  //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
    EPD.SetFont(FONT12);                                //选择字体，具体支持的字体见文档
    EPD.DrawUTF(0, 0, "Hello World");                   //绘制字符串
    EPD.DrawUTF(26, 0, "我喜欢墨水屏");                 //绘制字符串
    EPD.fontscale = 1;                                  //字体缩放系数改回1
    EPD.DrawXbm_P(100, 0, 12, 12, (uint8_t *)city_icon); //绘制图片
    EPD.EPD_Transfer_Full_BW((unsigned char *)EPD.EPDbuffer, 1); //将黑白图像传入缓存
    EPD.clearbuffer();
    EPD.fontscale = 2;
    EPD.DrawUTF(40, 0, "现在是红色");
    EPD.fontscale = 1;
    EPD.DrawXbm_P(100, 30, 12, 12, (uint8_t *)city_icon); //绘制图片
    EPD.EPD_Transfer_Full_RED((unsigned char *)EPD.EPDbuffer,1);
    Serial.printf("缓存图像绘制完毕，准备全刷 \n");
    EPD.EPD_Update();
    EPD.ReadBusy_long();//等待屏幕刷新完成后才继续往下运行
    EPD.deepsleep(); //让屏幕进入休眠模式
    Serial.println("全刷完毕");
}

void loop()
{
    delay(1); //防止看门狗咬
}
