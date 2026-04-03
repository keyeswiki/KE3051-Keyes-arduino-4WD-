//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 11
  IRremote Control Robot
  www.keyes-robot.com
*/
#include <MecanumCar_v2.h>
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2
#include <IRremote.h>
/****引入红外遥控头文件***/

int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600); //设置波特率为9600
  mecanumCar.Init(); //初始化七彩灯与电机驱动
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value)
    {
      case 0xFF02FD: mecanumCar.Stop();       break;  //停止
      case 0xFF629D: mecanumCar.Advance();    break;  //前进
      case 0xFFA857: mecanumCar.Back();       break;  //后退
      case 0xFF22DD: mecanumCar.Turn_Left();  break;  //左转
      case 0xFFC23D: mecanumCar.Turn_Right(); break;  //右转
    }
    irrecv.resume(); // Receive the next value
  }
}
//*************************************************************************
