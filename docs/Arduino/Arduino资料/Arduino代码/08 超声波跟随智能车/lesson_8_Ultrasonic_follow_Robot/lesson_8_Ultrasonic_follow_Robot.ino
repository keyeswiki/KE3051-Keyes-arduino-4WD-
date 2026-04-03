//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 8
  Ultrasonic follow Robot
  www.keyes-robot.com
*/
#include "MecanumCar_v2.h"
#include "Servo.h"

mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2
Servo myservo;    //定义一个舵机类实例

/*******超声波传感器接口*****/
#define EchoPin  13  //ECHO引脚接到D13
#define TrigPin  12  //TRIG引脚接到D12

void setup() {
  Serial.begin(9600); //启动串口监视器,并设置波特率为9600
  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式
  myservo.attach(9);  // 将D9上的舵机附加到舵机对象上
  myservo.write(90); //转动到90度
  delay(300);//延时0.3秒
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  int distance = get_distance();  //获取距离保存在distance变量
  Serial.println(distance);
  if (distance <= 15)  //后退的范围
  {
    mecanumCar.Back();
  }
  else if (distance <= 25)  //停止的范围
  {
    mecanumCar.Stop();
  }
  else if (distance <= 45) //前进的范围
  {
    mecanumCar.Advance();
  }
  else  //其它情况停止
  {
    mecanumCar.Stop();
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
