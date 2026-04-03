//*******************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 1
  Color LED
  www.keyes-robot.com
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2

void setup() {
  mecanumCar.Init();//初始化电机与七彩灯驱动
}

void loop() {
  mecanumCar.right_led(1);//开启右边七彩灯闪烁
  mecanumCar.left_led(1); //开启左边七彩灯闪烁
  delay(3000);            //延时3000毫秒
  mecanumCar.right_led(0); //关闭右边七彩灯闪烁
  mecanumCar.left_led(0);  //关闭左边七彩灯闪烁
  delay(1000);             //延时1000毫秒
}
//*******************************************************************
