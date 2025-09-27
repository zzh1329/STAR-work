#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(8, 9);  // 蓝牙模块 RX, TX
Servo myServo;            // 创建舵机对象

int servoPin = 5;         // 舵机连接引脚
int angle = 90;           // 舵机初始角度

void setup() {
  Serial.begin(9600);
  BT.begin(38400);        // 蓝牙通信波特率
  
  myServo.attach(servoPin); // 连接舵机到指定引脚
  myServo.write(angle);     // 设置舵机初始位置
  
  Serial.println("蓝牙舵机控制器已启动");
  Serial.println("发送指令格式:");
  Serial.println("0-180: 设置角度");
  Serial.println("L: 左转90度");
  Serial.println("R: 右转90度");
  Serial.println("C: 回到中心");
}

void loop() {
  // 检查蓝牙是否有数据
  if (BT.available()) {
    String command = BT.readString();  // 读取蓝牙数据
    command.trim();                    // 去除换行符等
    
    Serial.print("收到指令: ");
    Serial.println(command);
    
    // 处理控制指令
    processCommand(command);
  }
  
  delay(100); // 短暂延迟
}

void processCommand(String cmd) {
  // 如果是数字指令 (0-180度)
  if (isNumeric(cmd)) {
    int newAngle = cmd.toInt();
    if (newAngle >= 0 && newAngle <= 180) {
      angle = newAngle;
      myServo.write(angle);
      Serial.print("设置角度: ");
      Serial.println(angle);
      BT.println("角度设置为: " + String(angle));
    }
  }
  // 特殊指令处理
  else if (cmd == "L" || cmd == "l") {
    angle = 0;
    myServo.write(angle);
    BT.println("左转到底");
  }
  else if (cmd == "R" || cmd == "r") {
    angle = 180;
    myServo.write(angle);
    BT.println("右转到底");
  }
  else if (cmd == "C" || cmd == "c") {
    angle = 90;
    myServo.write(angle);
    BT.println("回到中心");
  }
  else if (cmd == "STATUS" || cmd == "status") {
    BT.println("当前角度: " + String(angle));
  }
  else {
    BT.println("未知指令，请发送: 0-180, L, R, C");
  }
}

// 检查字符串是否为数字
boolean isNumeric(String str) {
  for (byte i = 0; i < str.length(); i++) {
    if (!isDigit(str.charAt(i))) {
      return false;
    }
  }
  return true;
}