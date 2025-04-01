//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 10.1
  IRremote
  www.keyes-robot.com
*/

#include "ir.h"

IR IRreceive(A3);//红外接收接A3

void setup(){
  Serial.begin(9600); //设置波特率为9600
}

void loop() {
  int key = IRreceive.getKey();
  if (key != -1) {
    Serial.println(key);
  }
}
//*************************************************************************
