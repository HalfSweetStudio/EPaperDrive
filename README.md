# EPaperDrive
这是一个简单好用性能强大的Arduino墨水屏驱动库，支持目前市面上较常见的多种墨水屏。

## 我应该如何使用它？
请着重参考[例程](https://github.com/HalfSweetStudio/EPaperDrive/tree/main/examples)、[API手册](docs/API手册.md)以及[用户手册](docs/用户手册.md)，如果您遇到了例程不能使用的情况，请提交issue说明详细情况。

## 我应该采用什么样的驱动电路？
事实上，几乎所有的串口SPI的墨水屏驱动电路以及引脚定义都是相同的，如果您有微雪或者大连佳显等厂商提供的驱动板，您可以直接使用它。如果您是裸屏，那么我建议您采用这款[驱动板](https://oshwhub.com/ludas/mo-shui-ping-qu-dong)。需要注意的是，请您采用4-wire模式来驱动墨水屏，我们暂不支持3-wire模式。

## 这个驱动库支持什么MCU？
很遗憾，目前为止该驱动库仅支持ESP8266/ESP32或者别的带文件系统的MCU，我们会在之后重构整个驱动库来达到更好的兼容性。

## 有什么联系方式吗？
您可以发送邮件（HalfSweet@HalfSweet.cn）给我，或者加我的QQ好友（2522182733），当然，您也可以加入QQ群聊（735507661）与我们进行讨论。

## 你会适配新的屏幕吗？
当然可以！我们会逐渐适配一些常见的以及我们拥有的屏幕，当然，如果您想要适配您手上的屏幕，请您与我取得联系并邮寄相应的屏幕进行测试，

## 目前支持的屏幕？
下表即为目前支持的屏幕的名称（即`EPD_Set_Model`函数内填的内容，留空即为我暂不知道）
|屏幕名称|驱动芯片型号|参考链接|
|:---:|:---:|:---:|
|WX29|SSD1608|<https://www.waveshare.net/wiki/2.9inch_e-Paper_Module>|
|WF29|||
|OPM42|SSD1619||
|WF58|||
|WF29BZ03|||
|C154|||
|DKE42_3COLOR|SSD1619|<https://www.good-display.cn/product/214.html>|
|DKE29_3COLOR|SSD1680|<https://www.good-display.cn/product/391.html>|
|WF42|UC8176|<https://www.waveshare.net/wiki/4.2inch_e-Paper_Module#myresources>|
|WFT0290CZ10|UC8151C|<https://www.good-display.cn/product/210.html>|
|GDEY042Z98|SSD1683|<https://www.good-display.cn/product/378.html>|
|HINKE0266A15A0|SSD1675||

## 致谢
非常感谢Duck大佬的支持，这个驱动库最开始的架构也是出自于他，这是他的[个人主页](https://github.com/duck531a98)以及最开始的[开源链接](https://github.com/duck531a98/esp8266-weather-station-epaper),我入坑于电子便是受到了他的影响，同时也非常感谢他教会了我很多编程以及电子的知识，同时在我成长的道路上也一直支持鼓励着我。  
同时也非常感谢在我学习的路上支持着我的各位大佬，是你们的存在让我在漫天的bug中找到继续学习下去的动力。
