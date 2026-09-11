#include <IRremote.h>

// 红外接收引脚
const int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600); // 设置波特率
  // 开启红外接收
  irrecv.enableIRIn();
  Serial.println("红外遥控就绪，请按下遥控器按键");
}

void loop()
{
  // 判断是否收到红外信号
  if (irrecv.decode(&results))
  {
    Serial.print("红外按键码(HEX)：");
    Serial.println(results.value, HEX);
  irrecv.resume(); // 释放缓存，准备接收下一组信号
  }
}

