//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 2.2
  RGB2812
  www.keyes-robot.com
*/
#include <Adafruit_NeoPixel.h>

//创建一个用于控制rgb的类,名为rgb_2812,共4个灯珠,引脚连接到D10
Adafruit_NeoPixel rgb_2812 = Adafruit_NeoPixel(4, 10, NEO_GRB + NEO_KHZ800);

void setup() {
  rgb_2812.begin();   //启动rgb2818
  rgb_2812.setBrightness(150);  //初始化亮度(0~255)
  rgb_2812.clear();   //初始化所有NeoPixels为“关闭”状态
}

void loop() {
  uint8_t r = random(0, 255);
  uint8_t g = random(0, 255);
  uint8_t b = random(0, 255);
  for (uint8_t i = 0; i < 4; i++)
  {
    rgb_2812.setPixelColor(i, r, g, b);//第i+1个灯珠颜色为随机(r,g,b)
    rgb_2812.show();    //刷新显示
    delay(100); //等待一会儿
  }
}
//*************************************************************************
