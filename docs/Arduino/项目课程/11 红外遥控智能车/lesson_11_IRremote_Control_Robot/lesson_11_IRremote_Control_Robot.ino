//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 11
  IRremote Control Robot
  www.keyes-robot.com
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2

/****引入红外遥控头文件***/
#include "ir.h"

IR IRreceive(A3);//红外接收接A3

void setup()
{
  Serial.begin(9600); //设置波特率为9600
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  int key = IRreceive.getKey();
  if (key != -1) {
    Serial.println(key);
    switch (key)
    {
      case 64: mecanumCar.Stop();       break;  //停止
      case 70: mecanumCar.Advance();    break;  //前进
      case 21: mecanumCar.Back();       break;  //后退
      case 68: mecanumCar.Turn_Left();  break;  //左转
      case 67: mecanumCar.Turn_Right(); break;  //右转
    }
  }
}
//*************************************************************************
