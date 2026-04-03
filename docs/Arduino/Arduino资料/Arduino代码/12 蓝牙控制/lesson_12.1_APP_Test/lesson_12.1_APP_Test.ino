//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 12.1
  APP Test
  www.keyes-robot.com
*/

void setup() {
  Serial.begin(9600);//启动串口监视器设置波特率为9600
}

void loop() {
  if (Serial.available())//如果接收区非空
  {
    char ble_val = Serial.read();//读取蓝牙数据
    Serial.println(ble_val);//串口打印读取到的数据
  }
}
//*************************************************************************
