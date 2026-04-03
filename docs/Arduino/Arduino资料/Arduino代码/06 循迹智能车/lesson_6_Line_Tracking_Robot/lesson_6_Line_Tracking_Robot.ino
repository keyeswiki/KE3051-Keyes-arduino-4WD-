//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 6
  Line Tracking Robot
  www.keyes-robot.com
*/

#include "MecanumCar_v2.h"
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2

/*******循迹传感器引脚定义**********/
#define SensorLeft    A0   //左传感器输入引脚
#define SensorMiddle  A1   //中间传感器输入引脚
#define SensorRight   A2   //右传感器输入引脚


void setup() {
  /****循迹传感器接口全部设置为输入模式***/
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  uint8_t SL = digitalRead(SensorLeft);   //读取左边巡线传感器的值
  uint8_t SM = digitalRead(SensorMiddle); //读取中间巡线传感器的值
  uint8_t SR = digitalRead(SensorRight);  //读取右边巡线传感器的值
  if (SM == HIGH) {
    if (SL == LOW && SR == HIGH) {  // 右边是黑色，左边是白色，向右转
      mecanumCar.Turn_Right();
    }
    else if (SR == LOW && SL == HIGH) {  //左边是黑色，右边是白色，左转
      mecanumCar.Turn_Left();
    }
    else {  // 两边都是白色的，向前走
      mecanumCar.Advance();
    }
  }
  else {
    if (SL == LOW && SR == HIGH) { // 右边是黑色，左边是白色，向右转
      mecanumCar.Turn_Right();
    }
    else if (SR == LOW && SL == HIGH) {  // 右边是白色，左边是黑色，左转
      mecanumCar.Turn_Left();
    }
    else { // 全白色,停止
      mecanumCar.Stop();
    }
  }
}
//*************************************************************************
