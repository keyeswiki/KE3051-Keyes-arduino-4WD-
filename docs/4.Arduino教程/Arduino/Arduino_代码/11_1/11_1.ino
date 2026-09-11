#include <MecanumCar_v2.h>
#include <IRremote.h>

// I2C七彩灯与电机驱动 SDA=D3 SCL=D2
mecanumCar mecanumCar(3, 2);
// 红外接收引脚A3
const int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);  // 设置波特率为9600
  mecanumCar.Init();  // 初始化七彩灯与电机驱动
  irrecv.enableIRIn(); // 启动红外接收
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xFF02FD: mecanumCar.Stop();       break;  // 停止
      case 0xFF629D: mecanumCar.Advance();    break;  // 前进
      case 0xFFA857: mecanumCar.Back();       break;  // 后退
      case 0xFF22DD: mecanumCar.Turn_Left();  break;  // 左转
      case 0xFFC23D: mecanumCar.Turn_Right(); break;  // 右转
    }
    irrecv.resume(); // 释放缓存，等待下一帧红外信号
  }
}

