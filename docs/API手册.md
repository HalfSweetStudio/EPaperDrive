# EPaperDrive API手册
该手册的标题为函数声明，在正文部分会以此介绍函数的用法、参数和返回值。

## EPaperDrive(bool SPIMode, uint8_t CS, uint8_t RST, uint8_t DC, uint8_t BUSY, uint8_t CLK, uint8_t DIN)
* @brief 构造函数，初始化软硬SPI及引脚定义
* @param SPIMode 选择是硬件SPI还是软件SPI，0为软件，1为硬件（不采用硬件CS）
* @param CS CS脚
* @param RST RST脚
* @param DC DC脚
* @param BUSY BUSY脚
* @param CLK 时钟线，如果是硬件SPI可以不填
* @param DIN 数据线，如果是硬件SPI可以不填

## void EPD_Set_Model(uint8_t model)
* @brief 设置墨水屏的型号

* @param model 墨水屏的型号，目前支持的屏幕可在README里面查看

## void EPD_init_Full(void)
* @brief 墨水屏全刷的初始化

## void EPD_init_Part(void)
* @brief 墨水屏局刷的初始化

## void deepsleep(void)
* @brief 让墨水屏进入睡眠模式，节省功耗

## void EPD_Dis_Full(uint8_t *DisBuffer, uint8_t Label)
* @brief 全刷传入的图像  
* @param DisBuffer 传入的图像缓存指针  
* @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑

## EPD_Dis_Part(int xStart, int xEnd, int yStart, int yEnd, uint8_t *DisBuffer, uint8_t Label)
* @brief 局刷传入的图像  
* xStart 局刷区域x开始的坐标
* @param xEnd 局刷区域x结束的坐标
* @param yStart 局刷区域y开始的坐标
* @param yEnd 局刷区域y结束的坐标
* @param DisBuffer 传入的图像缓存指针
* @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑

## void EPD_Transfer_Full_BW(uint8_t *DisBuffer, uint8_t Label)
* @brief 直接向RAM中写全刷的黑白图片
* @param DisBuffer 应当写入的图像缓存指针
* @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑；4为向“OLD”RAM中写全黑

## void EPD_Transfer_Full_RED(uint8_t *DisBuffer, uint8_t Label)
* @brief 直接向RAM中写全刷的红色图片
* @param DisBuffer 应当写入的图像缓存指针
* @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全红

## void EPD_Transfer_Part(int xStart, int xEnd, int yStart, int yEnd, uint8_t *DisBuffer, uint8_t Label)
@brief 直接向RAM中写局刷的图像
* @param xStart 局刷区域x开始的坐标
* @param xEnd 局刷区域x结束的坐标
* @param yStart 局刷区域y开始的坐标
* @param yEnd 局刷区域y结束的坐标
* @param DisBuffer 传入的图像缓存指针
* @param Label 应该刷的图像，1为传入的缓存；2为全白；3为全黑

## void SetFS(FS *userFS)
* @brief 设置采用什么文件系统
* @param userFS 应当传入的文件系统的指针

## void SetHardSPI(SPIClass *spi)
* @brief 设置采用硬件spi的通道（用户请先初始化SPI之后再传入对应SPI的指针）
* @param spi 应当传入的SPI的指针

## void clearbuffer()
* @brief 清除之前所绘的图像缓存

## void SetFont(FONT fontindex)
* @brief 设置字体样式
* @param fontindex 字体样式，目前仅支持如下字体： 


|字体|
|:----:| 
|FONT12| 
|FONT16| 
|FONT32|
|FONT10|
|FONT70|
|FONT12_NUM|
|FONT24|
|FONT8|
|DIGI_NUM_100|
|ICON32|
|ICON80|
|ICON50|  

如果对字体的效果并不满意，可以参考[用户手册]()自行修改

## void DrawUTF(int16_t x, int16_t y, String code)
@brief 在图像缓存中画字符串
*
* @param x 字符串图像开始的x坐标
* @param y 字符串图像开始的y坐标
* @param code 字符串内容

## DrawUnicodeChar(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t *code)
@brief 在图像缓存中画字符（可以忽略，采用`DrawUTF`函数即可）
*
* @param x 开始的x坐标
* @param y 开始的y坐标
* @param width 字符的宽度
* @param height 字符的高度
* @param code 字符的指针

## DrawUnicodeStr(int16_t x, int16_t y, uint8_t width, uint8_t height, uint8_t strlength, uint8_t *code)
* @brief 在图像缓存中画指定长度的字符串（可以忽略，采用`DrawUTF`函数即可）
* @param x 开始的x坐标
* @param y 开始的y坐标
* @param width 字符的宽度
* @param height 字符的高度
* @param strlength 字符串的长度
* @param code 字符串指针

## void DrawYline(int start, int end, int y)
* @brief 在图像缓存中画竖线（一个像素）
* @param start 线开始的x坐标
* @param end 线结束的x坐标
* @param y 线的y坐标

## void DrawXline(int start, int end, int x)
* @brief 在图像缓存中画横线（一个像素）
* @param start 线开始的y坐标
* @param end 线结束的y坐标
* @param x 线的x坐标

## void DrawLine(int xstart, int ystart, int xend, int yend)
* @brief 在图像缓存中画直线
* @param xstart 线开始的x坐标
* @param ystart 线开始的y坐标
* @param xend 线结束的x坐标
* @param yend 线结束的y坐标

## void Inverse(int xStart, int xEnd, int yStart, int yEnd)
* @brief 反向一个区域的图像（黑变白，白变黑）
* @param xStart 这个区域开始的x坐标
* @param xEnd 这个区域结束的x坐标
* @param yStart 这个区域开始的y坐标
* @param yEnd 这个区域结束的y坐标

## void DrawWeatherChart(int xmin, int xmax, int ymin, int ymax, int point_n, int show_n, String tmax, String tmin, String code_d, String code_n, String text_d, String text_n, String date, String week)
* @brief 绘制天气温度变化曲线
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

## void DrawCircle(int x, int y, int r, bool fill)
 * @brief 在图像缓存中画圆
* @param x 圆心的x坐标
* @param y 圆心的y坐标
* @param r 半径长度
* @param fill 0为空心圆；1为实心圆

## void DrawBox(uint8_t x, int y, int w, int h)
* @brief 在图像缓存中画实心矩形
* @param x 开始的x坐标
* @param y 开始的y坐标
* @param w 矩形的宽度
* @param h 矩形的高度

## void DrawEmptyBox(int x, int y, int w, int h）
* @brief 在图像缓存中画空心矩形
* @param x 开始的x坐标
* @param y 开始的y坐标
* @param w 矩形的宽度
* @param h 矩形的高度

## void DrawChart(int x, int y, int w, int c1, int c2, int c3, int c4, int c5, int c6)
* @brief 在图像缓存中画水平方向的柱状图（显示空气质量数据的，不建议使用）
* @param x 开始的x坐标
* @param y 开始的y坐标
* @param w 图表的宽度
* @param c1 第1个数据
* @param c2 第2个数据
* @param c3 第3个数据
* @param c4 第4个数据
* @param c5 第5个数据
* @param c6 第6个数据

## void DrawCircleChart(int x, int y, int r, int w, int c1, int c2, int c3)
* @brief 在图像缓存中画圆环图表（显示空气质量数据的，不建议使用）
* @param x 开始的x坐标
* @param y 开始的y坐标
* @param r 圆环的半径
* @param w 圆环的宽度
* @param c1 第1个数据
* @param c2 第2个数据
* @param c3 第3个数据

## void drawXbm(int16_t xMove, int16_t yMove, int16_t width, int16_t height, uint8_t *xbm);
* @brief 在图像缓存中绘制图像
* @param xMove 开始的x坐标
* @param yMove 开始的y坐标
* @param width 图像的宽度
* @param height 图像的高度
* @param xbm 图像的指针

## void DrawXbm_P(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm)
* @brief 在图像缓存中画以PROGMEM类型储存图片
* @param xMove 开始的x坐标
* @param yMove 开始的y坐标
* @param width 图像的宽度
* @param height 图像的高度
* @param xbm 图像的指针

## void DrawXbm_p_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, const uint8_t *xbm, uint8_t level)
* @brief 在图像缓存中画以PROGMEM类型储存的灰度图片
* @param xMove 开始的x坐标
* @param yMove 开始的y坐标
* @param width 图像的宽度
* @param height 图像的高度
* @param xbm 图像的指针
* @param level 灰度的等级

## void DrawXbm_spiff_gray(int16_t xMove, int16_t yMove, int16_t width, int16_t height, uint8_t level)
* @brief 在图像缓存中画以文件系统储存的灰度图片
* @param xMove 开始的x坐标
* @param yMove 开始的y坐标
* @param width 图像的宽度
* @param height 图像的高度
* @param level 灰度的等级

## void EPD_Set_Contrast(uint8_t vcom)
* @brief 设置vcom（仅有OPM42这块屏需要在意，别的屏幕不用管）
* @param vcom vcom的等级

## void EPD_Update(void)
* @brief 墨水屏全刷更新(一般用户不需要关心)

## void EPD_Update_Part(void)
* @brief 墨水屏局刷更新(一般用户不需要关心)

## bool ReadBusy(void)
* @brief 等待BUSY信号变为空闲（最大200ms超时）(一般用户不需要关心)
* @return bool 1代表成功，0代表超时

## bool ReadBusy_long(void)
* @brief 等待BUSY信号变为空闲（最大2000ms超时）(一般用户不需要关心)
* @return bool 1代表成功，0代表超时

## void EPD_WriteCMD(uint8_t command)
* @brief 向墨水屏驱动芯片写入命令(一般用户不需要关心)
* @param command 命令的值

## void EPD_WriteData(uint8_t data)
* @brief 向墨水屏驱动芯片写入数据(一般用户不需要关心)
* @param data 数据的值