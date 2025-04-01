//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 10.2
  IRremote Control LED
  www.keyes-robot.com
*/
#include "MecanumCar_v2.h"
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2
#include "ir.h"

IR IRreceive(A3);//红外接收接A3
bool flag = true;

void setup(){
  mecanumCar.Init();//初始化电机与七彩灯驱动
}

void loop() {
  int key = IRreceive.getKey();
  if (key == 64 && flag == true) {
    mecanumCar.right_led(1);
    mecanumCar.left_led(1);
    flag = false;
  }else if (key == 64 && flag == false) {
    mecanumCar.right_led(0);
    mecanumCar.left_led(0);
    flag = true;
  }
}
//*************************************************************************
