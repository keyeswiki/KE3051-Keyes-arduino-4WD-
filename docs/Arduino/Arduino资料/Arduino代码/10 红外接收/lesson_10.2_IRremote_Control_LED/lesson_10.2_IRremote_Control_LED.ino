//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 10.2
  IRremote Control LED
  www.keyes-robot.com
*/
#include <MecanumCar_v2.h>
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2
#include <IRremote.h>

int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;
bool flag = true;

void setup(){
  mecanumCar.Init();//初始化电机与七彩灯驱动
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFF02FD && flag == true) //开灯的值
    {
    mecanumCar.right_led(1);
    mecanumCar.left_led(1);
    flag = false;
    }
     else if (results.value == 0xFF02FD && flag == false) //关灯的值
    {
    mecanumCar.right_led(0);
    mecanumCar.left_led(0);
    flag = true;
    }
    irrecv.resume(); // Receive the next value
  }
}
//*************************************************************************
