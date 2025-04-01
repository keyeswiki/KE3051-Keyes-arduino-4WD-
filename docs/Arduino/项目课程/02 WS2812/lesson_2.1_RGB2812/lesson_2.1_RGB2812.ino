//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 2.1
  RGB2812
  www.keyes-robot.com
*/
#include <Adafruit_NeoPixel.h>

//创建一个用于控制rgb的类,名为rgb_2812,共4个灯珠,引脚连接到D10
Adafruit_NeoPixel rgb_2812 = Adafruit_NeoPixel(4, 10, NEO_GRB + NEO_KHZ800);

void setup() {
  rgb_2812.begin();   //启动rgb2818
  rgb_2812.setBrightness(100);  //初始化设置亮度为100,(0~255)
  rgb_2812.clear();   //初始化所有NeoPixels为“关闭”状态


  rgb_2812.setPixelColor(0, 255, 0, 0);//第1个灯珠亮红
  rgb_2812.setPixelColor(1, 0, 255, 0);//第2个灯珠亮绿色
  rgb_2812.setPixelColor(2, 0, 0, 255);//第3个灯珠亮蓝
  rgb_2812.setPixelColor(3, 255, 255, 255);//第4个灯珠亮白色
  rgb_2812.show();    //刷新显示
}

void loop() {
}
//*************************************************************************
