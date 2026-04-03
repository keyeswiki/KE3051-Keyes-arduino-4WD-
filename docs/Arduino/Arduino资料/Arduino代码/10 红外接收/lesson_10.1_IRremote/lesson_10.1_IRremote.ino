//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 10.1
  IRremote
  www.keyes-robot.com
*/

#include <IRremote.h>

int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600); //设置波特率为9600
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
  Serial.println(results.value, HEX);
  irrecv.resume(); // Receive the next value
}
}
//*************************************************************************
