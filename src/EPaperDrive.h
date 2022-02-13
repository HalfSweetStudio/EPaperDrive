#pragma once

//#include "spline.h"

#include <Arduino.h>
#include <SPI.h>
#if defined(ESP8266)
#include "FS.h"
#else
#if defined(ESP32)
#include "FS.h"
#include <LittleFS.h>
#include <SPIFFS.h>
#include <FFat.h>
#endif
#endif
#include "WAVEFORM_SETTING_LUT.h"

extern uint8_t UNICODEbuffer[200];
extern String fontname;

#define EPD_CS_0 digitalWrite(_CS, LOW)
#define EPD_CS_1 digitalWrite(_CS, HIGH)
#define isEPD_CS digitalRead(_CS)

#define EPD_RST_0 digitalWrite(_RST, LOW)
#define EPD_RST_1 digitalWrite(_RST, HIGH)
#define isEPD_RST digitalRead(_RST)

#define EPD_DC_0 digitalWrite(_DC, LOW)
#define EPD_DC_1 digitalWrite(_DC, HIGH)

#define READ_EPD_BUSY digitalRead(_BUSY)

#define EPD_CLK_0 digitalWrite(_CLK, LOW)
#define EPD_CLK_1 digitalWrite(_CLK, HIGH)

#define EPD_DIN_0 digitalWrite(_DIN, LOW)
#define EPD_DIN_1 digitalWrite(_DIN, HIGH)

enum FONT
{
  FONT16 = 0,
  FONT32 = 1,
  FONT10 = 2,
  FONT12 = 3,
  FONT70 = 5,
  FONT12_NUM = 6,
  FONT24 = 7,
  FONT8 = 8,
  DIGI_NUM_100 = 9,
  ICON32 = 13,
  ICON80 = 12,
  ICON50 = 14,
};
enum epd_type
{
  WX29 = 0, // SSD1608
  WF29 = 1,
  OPM42 = 2, // SSD1619
  WF58 = 3,
  WF29BZ03 = 4,
  C154 = 5,
  DKE42_3COLOR = 6, // SSD1619
  DKE29_3COLOR = 7, // SSD1680
  WF42 = 8,
  WF32 = 9,
  WFT0290CZ10 = 10,    // UC8151C
  GDEY042Z98 = 11,     // SSD1683
  HINKE0266A15A0 = 12, // SSD1675
};

enum EPDFS
{
  littlefs = 0,
  spiffs = 1,
  fatfs = 2,
};
/*
 * 典型使用流程
 * 1.EPD_init_Full/EPD_init_Part初始化
 * 2.clearbuffer清除缓存图像
 * 3.SetFont设置字体
 * 4.fontscale=1设置字体缩放
 * 5.DrawUTF 绘制文字。图像等
 * 6.EPD_DisFull/EPD_Dis_Part更新屏幕图像
 * 7.deepsleep睡眠
 *
 * 屏幕有圆点的角为（0，0）点，x方向为垂直方向，y方向为水平方向
 */
class EPaperDrive
{
public:
  /**
   * @brief 构造函数，初始化软硬SPI及引脚定义
   *
   * @param SPIMode 选择是硬件SPI还是软件SPI，0为软件，1为硬件（不采用硬件CS）
   * @param CS CS脚
   * @param RST RST脚
   * @param DC DC脚
   * @param BUSY BUSY脚
   * @param CLK 时钟线，如果是硬件SPI可以不填
   * @param DIN 数据线，如果是硬件SPI可以不填
   */
  EPaperDrive(bool SPIMode, uint8_t CS, uint8_t RST, uint8_t DC, uint8_t BUSY, uint8_t CLK = 127, uint8_t DIN = 127);

  /**
   * @brief 构析函数，暂无作用
   *
   */
  ~EPaperDrive();

  /**
   * @brief 让墨水屏进入睡眠模式，节省功耗
   *
   */
  void deepsleep(void);

  uint8_t fontscale;                ///> 字体缩放，仅支持1，2
  uint8_t frame;                    //用于4灰度屏，fram=0,在2bit中的第一个bit中存储图像，frame=1在第二bit种存储图像
  uint8_t EPDbuffer[400 * 300 / 8]; ///>屏幕图像
  epd_type EPD_Type;

  /**
   * @brief 设置采用什么文件系统
   *
   * @param userFS 应当传入的文件系统的指针
   */
  void SetFS(fs::FS* FSType);

  /**
   * @brief 设置采用硬件spi的通道（用户请先初始化SPI之后再传入对应SPI的指针）
   *
   * @param spi 应当传入的SPI的指针
   */
  void SetHardSPI(SPIClass *spi);

  /**
   * @brief 设置墨水屏的型号
   *
   * @param model 墨水屏的型号，目前支持的在epd_type这个枚举里面
   */
  void EPD_Set_Model(uint8_t model);

  /**
   * @brief 墨水屏全刷的初始化
   *
   */
  void EPD_init_Full(void);

  /**
   * @brief 墨水屏局刷的初始化
   *
   */
  void EPD_init_Part(void);

  /**
   * @brief 全刷传入的图像
   *
   * @param DisBuffer 传入的图像缓存指针
   * @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑
   */
  void EPD_Dis_Full(uint8_t *DisBuffer, uint8_t Label); // 1正常2全白3全黑

  /**
   * @brief 局刷传入的图像
   *
   * @param xStart 局刷区域x开始的坐标
   * @param xEnd 局刷区域x结束的坐标
   * @param yStart 局刷区域y开始的坐标
   * @param yEnd 局刷区域y结束的坐标
   * @param DisBuffer 传入的图像缓存指针
   * @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑
   */
  void EPD_Dis_Part(int xStart, int xEnd, int yStart, int yEnd, uint8_t *DisBuffer, uint8_t Label);

  /**
   * @brief 直接向RAM中写全刷的黑白图片
   *
   * @param DisBuffer 应当写入的图像缓存指针
   * @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑；4为向“OLD”RAM中写全黑
   */
  void EPD_Transfer_Full_BW(uint8_t *DisBuffer, uint8_t Label);

  /**
   * @brief 直接向RAM中写全刷的红色图片
   *
   * @param DisBuffer 应当写入的图像缓存指针
   * @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全红
   */
  void EPD_Transfer_Full_RED(uint8_t *DisBuffer, uint8_t Label);

  /**
   * @brief 直接向RAM中写局刷的图像
   *
   * @param xStart 局刷区域x开始的坐标
   * @param xEnd 局刷区域x结束的坐标
   * @param yStart 局刷区域y开始的坐标
   * @param yEnd 局刷区域y结束的坐标
   * @param DisBuffer 传入的图像缓存指针
   * @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑
   */
  void EPD_Transfer_Part(int xStart, int xEnd, int yStart, int yEnd, uint8_t *DisBuffer, uint8_t Label);

  /**
   * @brief 设置字体样式
   *
   * @param fontindex 字体样式，目前仅支持FONT枚举里面的
   */
  void SetFont(FONT fontindex);

  /**
   * @brief 在图像缓存中画字符串
   *
   * @param x 字符串图像开始的x坐标
   * @param y 字符串图像开始的y坐标
   * @param code 字符串内容
   */
  void DrawUTF(int16_t x, int16_t y, String code);

  /**
   * @brief 在图像缓存中画字符
   *
   * @param x 开始的x坐标
   * @param y 开始的y坐标
   * @param width 字符的宽度
   * @param height 字符的高度
   * @param code 字符的指针
   */
  void DrawUnicodeChar(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t *code);

  /**
   * @brief 在图像缓存中画指定长度的字符串
   *
   * @param x 开始的x坐标
   * @param y 开始的y坐标
   * @param width 字符的宽度
   * @param height 字符的高度
   * @param strlength 字符串的长度
   * @param code 字符串指针
   */
  void DrawUnicodeStr(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t strlength, uint8_t *code);

  /**
   * @brief 清除之前所绘的图像缓存
   *
   */
  void clearbuffer();

  /**
   * @brief 在图像缓存中画竖线（一个像素）
   *
   * @param start 线开始的x坐标
   * @param end 线结束的x坐标
   * @param y 线的y坐标
   */
  void DrawYline(int start, int end, int y); //画竖线

  /**
   * @brief 在图像缓存中画横线（一个像素）
   *
   * @param start 线开始的y坐标
   * @param end 线结束的y坐标
   * @param x 线的x坐标
   */
  void DrawXline(int start, int end, int x); //画横线

  /**
   * @brief 在图像缓存中画直线
   *
   * @param xstart 线开始的x坐标
   * @param ystart 线开始的y坐标
   * @param xend 线结束的x坐标
   * @param yend 线结束的y坐标
   */
  void DrawLine(int xstart, int ystart, int xend, int yend);

  /**
   * @brief 反向一个区域的图像（黑变白，白变黑）
   *
   * @param xStart 这个区域开始的x坐标
   * @param xEnd 这个区域结束的x坐标
   * @param yStart 这个区域开始的y坐标
   * @param yEnd 这个区域结束的y坐标
   */
  void Inverse(int xStart, int xEnd, int yStart, int yEnd);

  /**
   * @brief 绘制天气温度变化曲线
   *
   * @param xmin 绘制区域中开始的x坐标
   * @param xmax 绘制区域中结束的x坐标
   * @param ymin 绘制区域中开始的y坐标
   * @param ymax 绘制区域中结束的y坐标
   * @param point_n 传入的天气数据的数量
   * @param show_n 需要显示的天气数据的数量
   * @param tmax 需要显示的这几天每天温度的最大值（如12,13,14,15）
   * @param tmin 需要显示的这几天每天温度的最小值（如2,3,4,5）
   * @param code_d 需要显示的这几天每天温度最大值的图标对应的字符
   * @param code_n 需要显示的这几天每天温度最小值的图标对应的字符
   * @param text_d 需要显示的这几天每天温度最大值对应的天气状况
   * @param text_n 需要显示的这几天每天温度最小值对应的天气状况
   * @param date 我也不知道这是啥，看函数定义里面好像没啥用
   * @param week 需要显示的这几天每天是星期几（例如1,2,3,4）
   */
  void DrawWeatherChart(int xmin, int xmax, int ymin, int ymax, int point_n, int show_n, String tmax, String tmin, String code_d, String code_n, String text_d, String text_n, String date, String week); //绘制天气温度变化曲线

  /**
   * @brief 在图像缓存中画圆
   *
   * @param x 圆心的x坐标
   * @param y 圆心的y坐标
   * @param r 半径长度
   * @param fill 0为空心圆；1为实心圆
   */
  void DrawCircle(int x, int y, int r, bool fill); //画圆圈，xy圆心，r半径

  /**
   * @brief 在图像缓存中画实心矩形
   *
   * @param x 开始的x坐标
   * @param y 开始的y坐标
   * @param w 矩形的宽度
   * @param h 矩形的高度
   */
  void DrawBox(uint8_t x, int y, int w, int h); //画矩形，填充

  /**
   * @brief 在图像缓存中画空心矩形
   *
   * @param x 开始的x坐标
   * @param y 开始的y坐标
   * @param w 矩形的宽度
   * @param h 矩形的高度
   */
  void DrawEmptyBox(int x, int y, int w, int h); //画矩形，空心

  /**
   * @brief 在图像缓存中画水平方向的柱状图（显示空气质量数据的，不建议使用）
   *
   * @param x 开始的x坐标
   * @param y 开始的y坐标
   * @param w 图表的宽度
   * @param c1 第1个数据
   * @param c2 第2个数据
   * @param c3 第3个数据
   * @param c4 第4个数据
   * @param c5 第5个数据
   * @param c6 第6个数据
   */
  void DrawChart(int x, int y, int w, int c1, int c2, int c3, int c4, int c5, int c6); //画水平方向的柱状图，w图表宽度，c1-C6变量

  /**
   * @brief 在图像缓存中画圆环图表（显示空气质量数据的，不建议使用）
   *
   * @param x 开始的x坐标
   * @param y 开始的y坐标
   * @param r 圆环的半径
   * @param w 圆环的宽度
   * @param c1 第1个数据
   * @param c2 第2个数据
   * @param c3 第3个数据
   */
  void DrawCircleChart(int x, int y, int r, int w, int c1, int c2, int c3); //画圆环图表，r半径，w圆环宽，c1-c3变量

  /**
   * @brief 在图像缓存中绘制图像
   *
   * @param xMove 开始的x坐标
   * @param yMove 开始的y坐标
   * @param width 图像的宽度
   * @param height 图像的高度
   * @param xbm 图像的指针
   */
  void drawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, uint8_t *xbm); //绘制图像

  /**
   * @brief 在图像缓存中画以PROGMEM类型储存图片
   *
   * @param xMove 开始的x坐标
   * @param yMove 开始的y坐标
   * @param width 图像的宽度
   * @param height 图像的高度
   * @param xbm 图像的指针
   */
  void DrawXbm_P(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm);

  /**
   * @brief 在图像缓存中画以PROGMEM类型储存的灰度图片
   *
   * @param xMove 开始的x坐标
   * @param yMove 开始的y坐标
   * @param width 图像的宽度
   * @param height 图像的高度
   * @param xbm 图像的指针
   * @param level 灰度的等级
   */
  void DrawXbm_p_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm, uint8_t level);

  /**
   * @brief 在图像缓存中画以文件系统储存的灰度图片
   *
   * @param xMove 开始的x坐标
   * @param yMove 开始的y坐标
   * @param width 图像的宽度
   * @param height 图像的高度
   * @param level 灰度的等级
   */
  void DrawXbm_spiff_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, uint8_t level);

  /**
   * @brief 设置vcom（仅有OPM42这块屏需要在意，别的屏幕不用管）
   *
   * @param vcom vcom的等级
   */
  void EPD_Set_Contrast(uint8_t vcom);

  /**
   * @brief 墨水屏全刷更新
   *
   */
  void EPD_Update(void);

  /**
   * @brief 墨水屏局刷更新
   *
   */
  void EPD_Update_Part(void);

  /**
   * @brief 等待BUSY信号变为空闲（最大200ms超时）
   *
   * @return bool 1代表成功，0代表超时
   */
  bool ReadBusy(void);

  /**
   * @brief 等待BUSY信号变为空闲（最大2000ms超时）
   *
   * @return bool 1代表成功，0代表超时
   */
  bool ReadBusy_long(void);

  /**
   * @brief 向墨水屏驱动芯片写入命令
   *
   * @param command 命令的值
   */
  void EPD_WriteCMD(uint8_t command);

  /**
   * @brief 向墨水屏驱动芯片写入数据
   *
   * @param data 数据的值
   */
  void EPD_WriteData(uint8_t data);

  /**
   * @brief 向墨水屏驱动芯片中写命令和数据（第一个字节为命令，剩下的均为数据）
   *
   * @param value 要写的所有字节的指针
   * @param datalen 要写的所有字节的长度
   */
  void EPD_Write(uint8_t *value, uint8_t datalen);

  void EPD_WriteDispRam_Old(unsigned int XSize, unsigned int YSize, uint8_t *Dispbuff, unsigned int offset, uint8_t label);
    void EPD_WriteDispRam(unsigned int XSize, unsigned int YSize, uint8_t *Dispbuff, unsigned int offset, uint8_t label);
    void EPD_SetRamPointer(uint16_t addrX, uint8_t addrY, uint8_t addrY1);


private:
  uint8_t _CS;
  uint8_t _RST;
  uint8_t _DC;
  uint8_t _BUSY;
  uint8_t _CLK;
  uint8_t _DIN;
  bool _SPIMode;

  fs::FS *UserFS;


  SPIClass *MySPI;

  uint8_t FontIndex;

  int xDot;
  int yDot;
  int16_t CurrentCursor;
  uint8_t fontwidth;
  uint8_t fontheight;

  void SPI_Write(uint8_t value);
  void driver_delay_xms(unsigned long xms);

  void EPD_WriteDispRam_RED(unsigned int XSize, unsigned int YSize, uint8_t *Dispbuff, unsigned int offset, uint8_t label);
  // void EPD_SetRamArea(uint16_t Xstart,uint16_t Xend,uint8_t Ystart,uint8_t Ystart1,uint8_t Yend,uint8_t Yend1);
  
  void EPD_WirteLUT(uint8_t *LUTvalue, uint8_t Size);

  void EPD_Init(void);
  void EPD_WriteCMD_p1(uint8_t command, uint8_t para);
  
  void EPD_SetRamArea(uint16_t Xstart, uint16_t Xend, uint8_t Ystart, uint8_t Ystart1, uint8_t Yend, uint8_t Yend1);

  int getIcon(int weathercodeindex);
  void SetPixel(int16_t x, int16_t y);
  void InversePixel(int16_t x, int16_t y);
  void DrawUTF(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t *code);
  int UTFtoUNICODE(uint8_t *code);


};
