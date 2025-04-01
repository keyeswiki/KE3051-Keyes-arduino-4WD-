//*************************************************************************
/*
  Keyes arduino 4WD 麦克纳姆轮小车
  lesson 12.2
  APP Control Robot
  www.keyes-robot.com
*/
#include "MecanumCar_v2.h"
#include <Adafruit_NeoPixel.h>
#include "ir.h"
#include "Servo.h"

mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2
//创建一个用于控制rgb的类,名为rgb_2812,共4个灯珠,引脚连接到D10
Adafruit_NeoPixel rgb_2812 = Adafruit_NeoPixel(4, 10, NEO_GRB + NEO_KHZ800);
Servo myservo;
IR IRreceive(A3);//红外接收接A3

/*******超声波传感器接口*****/
#define EchoPin  13  //ECHO to D13
#define TrigPin  12  //TRIG to D12

/*******循迹传感器引脚定义**********/
#define SensorLeft    A0   //左传感器输入引脚
#define SensorMiddle  A1   //中间传感器输入引脚
#define SensorRight   A2   //右侧传感器输入引脚

String speed_str1 = "0";

String speed_str2 = "0";

int color_num = 0;
char ble_val;

void setup() {
  Serial.begin(9600);  //设置蓝牙串波特率为9600
  pinMode(EchoPin, INPUT);    //ECHO引脚设置为输入模式
  pinMode(TrigPin, OUTPUT);   //TRIG引脚设置为输出模式

  /****循迹传感器接口全部设置为输入模式***/
  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);
  myservo.attach(9);  // 将D9上的舵机附加到舵机对象上
  myservo.write(90);
  delay(500);

  rgb_2812.begin();   //启动rgb2818
  rgb_2812.setBrightness(255);  //初始化亮度(0~255)
  rgb_2812.show();   //初始化刷新
  mecanumCar.Init(); //初始化七彩灯与电机驱动
}

void loop() {
  int key = IRreceive.getKey();
  if (key != -1) {
    Serial.println(key);
    switch (key)
    {
      case 64: mecanumCar.Stop();       break;  //停止
      case 70: mecanumCar.Advance();    break;  //前进
      case 21: mecanumCar.Back();       break;  //后退
      case 68: mecanumCar.Turn_Left();  break;  //左转
     case 67: mecanumCar.Turn_Right(); break;  //右转
   }
 }
  if (Serial.available())//如果接收缓冲区非空
  {
    ble_val = Serial.read();//读取蓝牙数据
    Serial.println(ble_val);//串口打印读取到的数据
    switch (ble_val)
    {
      /*********************小车行驶************************/
      case 's': mecanumCar.Stop();       break;  //停止
      case 'a': mecanumCar.Advance();    break;  //前进
      case 'c': mecanumCar.Back();       break;  //后退
      case 'b': mecanumCar.Turn_Left();  break;  //左转
      case 'd': mecanumCar.Turn_Right(); break;  //右转
      case 'k': mecanumCar.L_Move();     break;  //左移
      case 'h': mecanumCar.R_Move();     break;  //右移
      case 'l': mecanumCar.LU_Move();    break;  //左上移
      case 'j': mecanumCar.LD_Move();    break;  //左下移
      case 'g': mecanumCar.RU_Move();    break;  //右上移
      case 'i': mecanumCar.RD_Move();    break;  //右下移
      case 'e': mecanumCar.drift_left(); break;  //漂移
      case 'f': mecanumCar.drift_right(); break; //漂移

      case 'p': Line_Tracking();   break;  //循迹
      case 'q': ult_following();   break;  //跟随
      case 'r': ult_avoiding();    break;  //避障

      /*********************小车灯光*************************/
      case 't': mecanumCar.right_led(1);  mecanumCar.left_led(1); break;  //开七彩灯
      case 'u': mecanumCar.right_led(0);  mecanumCar.left_led(0); break;  //关七彩灯
      case 'm': color_num++; showColor(); break;  //切换2812灯珠颜色
      case 'o': rgb_2812.clear(); rgb_2812.show(); break;  //关闭2812灯珠
      case 'n': color_num--; showColor(); break;  //切换2812灯珠颜色
      /*********************小车调速*************************/
      case 'v':   /*读左前方电机M2的速度*/
        speed_str1 = Serial.readStringUntil('#');  //第一次接收到的速度数据，保存
        speed_str2 = Serial.readStringUntil('#');  //第二次接收到速度数据，保存
        speed_Upper_L = String(speed_str2).toInt();      //速度值为字符串格式，需要转换为整型
        speed_Upper_L = map(speed_Upper_L, 0, 100, 0, 255);  //从0~100映射到0~255
        //Serial.println(speed_Upper_L);
        break;
      case 'w':   /*读左后方电机M3的速度*/
        speed_str1 = Serial.readStringUntil('#'); 
        speed_str2 = Serial.readStringUntil('#');
        speed_Lower_L = String(speed_str2).toInt();
        speed_Lower_L = map(speed_Lower_L, 0, 100, 0, 255);
        //Serial.println(speed_Lower_L);
        break;
      case 'x':   /*读右前方电机M1的速度*/
        speed_str1 = Serial.readStringUntil('#');
        speed_str2 = Serial.readStringUntil('#');
        speed_Upper_R = String(speed_str2).toInt();
        speed_Upper_R = map(speed_Upper_R, 0, 100, 0, 255);
        //Serial.println(speed_Upper_R);
        break;
      case 'y':   /*读右后方电机M4的速度*/
        speed_str1 = Serial.readStringUntil('#');
        speed_str2 = Serial.readStringUntil('#');
        speed_Lower_R = String(speed_str2).toInt();
        speed_Lower_R = map(speed_Lower_R, 0, 100, 0, 255);
        //Serial.println(speed_Lower_R);
        break;
    
      default: break;
    } 
  }
}


/*********************RGB2812显示*******************************/
void showColor() {
  //  Serial.print("color num:"); //用于串口调试
  //  Serial.println(color_num);
  //  这里设置只了7种颜色，可以自己添加
  if (color_num > 6)color_num = 0;
  if (color_num < 0)color_num = 6;
  switch (color_num) {
    case  0:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 255, 0, 0);  //第i个灯珠亮红色
      }
      break;
    case  1:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 255, 80, 0); //第i个灯珠亮橙色
      }
      break;
    case  2:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 255, 255, 0); //第i个灯珠亮黄色
      }
      break;
    case  3:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 0, 255, 0);   //第i个灯珠亮绿色
      }
      break;
    case  4:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 0, 0, 255);   //第i个灯珠亮蓝色
      }
      break;
    case  5:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 0, 255, 255); //第i个灯珠亮靛色
      }
      break;
    case  6:
      for (int i = 0; i < 4; i++) {
        rgb_2812.setPixelColor(i, 160, 32, 240);//第i个灯珠亮紫色
      }
      break;
    default : break;
  }
  rgb_2812.show();                        //刷新显示
}

/*********************循迹*******************************/
void Line_Tracking(void) {   //循黑线
  while (1)
  {
    uint8_t SL = digitalRead(SensorLeft);   //读取左边巡线传感器的值
    uint8_t SM = digitalRead(SensorMiddle); //读取中间巡线传感器的值
    uint8_t SR = digitalRead(SensorRight);  //读取右边巡线传感器的值
    if (SM == HIGH) {
      if (SL == LOW && SR == HIGH) {  // 右边是黑色，左边是白色，向右转
        mecanumCar.Turn_Right();
      }
      else if (SR == LOW && SL == HIGH) {  // 左边是黑色，右边是白色，左转
        mecanumCar.Turn_Left();
      }
      else {  // 两边都是白色的，向前走
        mecanumCar.Advance();
      }
    }
    else {
      if (SL == LOW && SR == HIGH) { // 右边是黑色，左边是白色，向右转
        mecanumCar.Turn_Right();
      }
      else if (SR == LOW && SL == HIGH) {  // 右边是白色，左边是黑色，左转
        mecanumCar.Turn_Left();
      }
      else { // 全白色,停止
        mecanumCar.Stop();
      }
    }
    if (Serial.available())//如果接收缓冲区非空
    {
      ble_val = Serial.read();//读取蓝牙数据
      if (ble_val == 's') {
        mecanumCar.Stop();
        break;
      }
    }
  }
}


/*********************超声波跟随*******************************/
void ult_following(void)
{
  while (1)
  {
    int distance = get_distance();  //获取距离保存在distance变量
    //Serial.println(distance);
    if (distance <= 15)  //后退的范围
    {
      mecanumCar.Back();
    }
    else if (distance <= 25)  //停止的范围
    {
      mecanumCar.Stop();
    }
    else if (distance <= 45) //前进的范围
    {
      mecanumCar.Advance();
    }
    else  //其它情况停止
    {
      mecanumCar.Stop();
    }
    if (Serial.available())//如果接收缓冲区非空
    {
      ble_val = Serial.read();//读取蓝牙数据
      if (ble_val == 's') {
        mecanumCar.Stop();
        break;
      }
    }
  }
}


/*********************超声波避障*******************************/
void ult_avoiding(void)
{
  int distance_M, distance_L, distance_R;
  while (1)
  {
    distance_M = get_distance();  //获取距离保存在distance变量
    if (distance_M < 20) {//当测到前方的距离小于20cm时
      mecanumCar.Stop();  //机器人停止
      delay(500); //延时500ms
      myservo.write(180);  //超声波云台左转
      delay(500); //延时500ms
      distance_L = get_distance();  //把超声波测到左边的距离赋给变量distance_L
      delay(100); //稳定读取值
      myservo.write(0); //超声波云台右转
      delay(500); //延时500ms
      distance_R = get_distance(); //把超声波测到右边的距离赋给变量distance_R
      delay(100); //稳定读取值

      myservo.write(90);  //回到90度位置
      delay(500);
      if (distance_L > distance_R) { //左边的距离大于右边时
        mecanumCar.Turn_Left();  //机器人左转
        delay(300);  //左转700ms
      } else {
        mecanumCar.Turn_Right(); //机器人右转
        delay(300);
      }
    }
    else { //如果测到前方的距离>=20cm时，机器人前进
      mecanumCar.Advance(); //前进
    }
    if (Serial.available())//如果接收缓冲区非空
    {
      ble_val = Serial.read();//读取蓝牙数据
      if (ble_val == 's') {
        mecanumCar.Stop();
        break;
      }
    }
  }
}


/*********************超声波测距*******************************/
int get_distance(void) {    //超声波测距
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //给TRIG至少10us的高电平以触发
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58.2; //计算出距离
  delay(30);
  return dis;
}
//*************************************************************************
