#include <Servo.h> // 导入库文件

#define  servo_pin  9  // 舵机接D9
Servo myservo;    // 定义一个舵机类实例

void setup() {
  myservo.attach(servo_pin);    // 舵机引脚连接到D9
}

void loop() {
  for (uint8_t angle = 0; angle < 180; angle++) // 从0到180度
  {
    myservo.write(angle); // 转动到angle角度
    delay(15);  // 等待一会,以免转得太快
  }
  for (uint8_t angle = 180; angle > 0; angle--) // 从180到0度
  {
    myservo.write(angle); // 转动到angle角度
    delay(15);
  }
}
