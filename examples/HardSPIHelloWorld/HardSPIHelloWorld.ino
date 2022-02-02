#include <Arduino.h>
#include <EPaperDrive.h>
//包含你需要使用的文件系统,例如：
#include <LittleFS.h>

#define BAUD_SPEED 74880 //串口调试的波特率，可自行修改

#define CS 15
#define RST 2
#define DC 0
#define BUSY 4

EPaperDrive EPD(1, CS, RST, DC, BUSY); //驱动库的实例化，此处为使用硬件SPI

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
#if defined(ESP8266)
  SPI.begin();
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
#else
#if defined(ESP32)
  SPIClass SPI(HSPI); //可自行更换SPI通道
  SPI.begin();
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
#else
#error 不支持您的MCU
#endif
#endif
  EPD.SetHardSPI(&SPI);
  LittleFS.begin();
  EPD.SetFS(&LittleFS); //设置存放字体的文件系统，传入的为该文件系统的操作指针，可自行修改

  EPD.EPD_Set_Model(HINKE0266A15A0);                  //设置屏幕类型，具体型号可以参考文档
  EPD.EPD_init_Full();                                //全刷初始化，使用全刷波形
  EPD.clearbuffer();                                  //清空缓存(全白)
  EPD.fontscale = 2;                                  //字体缩放系数(支持1和2,对图片也有效，用完记得重新改成1)
  EPD.SetFont(FONT12);                                //选择字体，具体支持的字体见文档
  EPD.DrawUTF(0, 0, "Hello World");                   //绘制字符串
  EPD.DrawUTF(26, 0, "我喜欢墨水屏");                 //绘制字符串
  EPD.fontscale = 1;                                  //字体缩放系数改回1
  EPD.DrawXbm_P(60, 0, 12, 12, (uint8_t *)city_icon); //绘制图片
  Serial.printf("缓存图像绘制完毕，准备全刷 \n");
  EPD.EPD_Dis_Full((uint8_t *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片全刷屏幕
  EPD.deepsleep();                               //让屏幕进入休眠模式
  Serial.println("全刷完毕");

  delay(5000);

  EPD.EPD_init_Part(); //局刷的初始化
  EPD.clearbuffer();
  EPD.fontscale = 2;
  EPD.SetFont(FONT12);
  EPD.DrawUTF(0, 0, "现在是局刷");
  Serial.printf("开始局刷 \n");
  EPD.EPD_Dis_Part(0, 23, 0, 199, (uint8_t *)EPD.EPDbuffer, 1); //将缓存中的图像传给屏幕控制芯片局新屏幕
  Serial.printf("局刷结束 \n");
  EPD.deepsleep();
}

void loop()
{
  delay(1); //防止看门狗咬
}
