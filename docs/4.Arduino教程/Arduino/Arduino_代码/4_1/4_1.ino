#include "MecanumCar_v2.h" // 导入库文件

mecanumCar mecanumCar(3, 2);  // sda-->D3,scl-->D2

void setup() {
  mecanumCar.Init();  // 初始化麦轮车驱动
}

void loop() {
  mecanumCar.Advance();  // 前进
  delay(2000);           // 等待2秒  
  mecanumCar.Back();     // 后退
  delay(2000);
  mecanumCar.Turn_Left(); // 左转
  delay(2000);
  mecanumCar.Turn_Right(); // 右转
  delay(2000);
  mecanumCar.Stop();      // 停止
  delay(1000);
}
