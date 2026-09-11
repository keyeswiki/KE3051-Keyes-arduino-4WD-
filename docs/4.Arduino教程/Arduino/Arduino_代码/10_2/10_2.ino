#include <MecanumCar_v2.h>
#include <IRremote.h>

// I2C七彩灯与电机驱动 SDA=D3 SCL=D2
mecanumCar mecanumCar(3, 2);
// 红外接收引脚A3
const int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;

// 灯光状态标记
bool flag = true;

void setup() {
  Serial.begin(9600);   // 开启串口，波特率9600
  mecanumCar.Init();   // 初始化电机与七彩灯驱动
  irrecv.enableIRIn();  // 启动红外接收 
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFF02FD && flag == true) { // 开灯的值
       mecanumCar.right_led(1);
       mecanumCar.left_led(1);
       flag = false;
    }
    else if (results.value == 0xFF02FD && flag == false) { // 关灯的值
       mecanumCar.right_led(0);
       mecanumCar.left_led(0);
       flag = true;
    }
    irrecv.resume(); // 释放缓存，准备接收下一组信号
  }
}

