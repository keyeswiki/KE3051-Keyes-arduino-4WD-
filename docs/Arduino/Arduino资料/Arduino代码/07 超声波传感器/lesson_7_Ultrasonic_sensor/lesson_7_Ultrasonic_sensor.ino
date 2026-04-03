//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 7
  Ultrasonic sensor
  www.keyes-robot.com
*/

/*******超声波传感器接口*****/
#define EchoPin  13  //ECHO引脚接到D13
#define TrigPin  12  //TRIG引脚接到D12

void setup() {
  Serial.begin(9600); //设置波特率为9600
  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式
}

void loop() {
  float distance = Get_Distance();  //获取距离保存在distance变量
  Serial.print("ditance:");
  Serial.print(distance);
  Serial.println("cm");
  delay(100);
}

float Get_Distance(void) {    //超声波测距
  float dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //给TRIG至少10us的高电平以触发
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) /58.2;  //计算出距离
  delay(50);
  return dis;
}
//*************************************************************************
