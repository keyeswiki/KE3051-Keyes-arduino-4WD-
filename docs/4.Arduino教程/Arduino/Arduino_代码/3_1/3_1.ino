#define  servo_pin  9   // 舵机接D9

void setup() {
  pinMode(servo_pin, OUTPUT);    // 舵机引脚设置为输出模式
}

void loop() {
  for (uint8_t angle = 0; angle < 180; angle++){ // 舵机角度从0°逐渐加1到180°
    servopulse(servo_pin, angle);
  }
  for (uint8_t angle = 180; angle > 0; angle--){ // 舵机角度从180°逐渐减1到0°
    servopulse(servo_pin, angle);
  }
}

void servopulse(int pin, int myangle) {   // 脉冲函数
  int pulsewidth = map(myangle, 0, 180, 500, 2500); // 将角度映射到脉宽
  //输出脉冲
  digitalWrite(pin, HIGH);        // 将舵机接口电平至高
  delayMicroseconds(pulsewidth);  // 延时脉宽值的微秒数
  digitalWrite(pin, LOW);         // 将舵机接口电平至低
  delay(20 - pulsewidth / 1000);  // 周期为20ms
}

