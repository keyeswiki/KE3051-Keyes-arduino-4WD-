//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 5
  Line Tracking Sensor
  www.keyes-robot.com
*/
/*******循迹传感器引脚定义**********/
#define SensorLeft    A0   //左传感器输入引脚
#define SensorMiddle  A1   //中间传感器输入引脚
#define SensorRight   A2   //右传感器输入引脚


void setup() {
  Serial.begin(9600); //启动串口监视器,并设置波特率为9600
  /****循迹传感器接口全部设置为输入模式***/
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);
}

void loop() {
  uint8_t SL = digitalRead(SensorLeft); //读取左边巡线传感器的值
  uint8_t SM = digitalRead(SensorMiddle); //读取中间巡线传感器的值
  uint8_t SR = digitalRead(SensorRight); //读取右边巡线传感器的值
  Serial.print("Left:");  //串口打印信息
  Serial.print(SL);
  Serial.print("  Middle:");
  Serial.print(SM);
  Serial.print("  Right:");
  Serial.print(SR);
  Serial.println(); //换行
  delay(100);
}
//*************************************************************************
