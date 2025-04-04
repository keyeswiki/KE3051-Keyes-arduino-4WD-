//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 9
  Ultrasonic obstacle avoidance Robot
  www.keyes-robot.com
*/
#include "MecanumCar_v2.h"
#include "Servo.h"

mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2
Servo myservo;    //定义一个舵机类实例

/*******超声波传感器接口*****/
#define EchoPin  13  //ECHO引脚接到D13
#define TrigPin  12  //TRIG引脚接到D12

int distance_M, distance_L, distance_R;

void setup() {
  myservo.attach(9);    //舵机引脚连接到GP9
  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式
  myservo.write(90); //转动到90度
  delay(300);
}

void loop() {
  distance_M = get_distance();  //获取距离保存在distance变量
  if (distance_M < 20) {//当测到前方的距离小于20cm时
    mecanumCar.Stop();  //机器人停止
    delay(500); //延时500ms
    myservo.write(180);  //超声波云台左转
    delay(500); //延时500ms
    distance_L = get_distance();  //把超声波测到左边的距离赋给变量distance_L
    delay(100); //稳定读取值
    myservo.write(0); //超声波云台右转
    delay(500); //延时500ms
    distance_R = get_distance(); //把超声波测到右边的距离赋给变量distance_R
    delay(100); //稳定读取值

    myservo.write(90);  //回到90度位置
    delay(500);
    if (distance_L > distance_R) { //左边的距离大于右边时
      mecanumCar.Turn_Left();  //机器人左转
      delay(300);  //左转700ms
    } else {
      mecanumCar.Turn_Right(); //机器人右转
      delay(300);
    }
  }
  else { //如果测到前方的距离>=20cm时，机器人前进
    mecanumCar.Advance(); //前进
  }
}

/*********************超声波测距*******************************/
int get_distance(void) {    //超声波测距
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //给TRIG至少10us的高电平以触发
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58.2; //计算出距离
  delay(30);
  return dis;
}
//*************************************************************************
