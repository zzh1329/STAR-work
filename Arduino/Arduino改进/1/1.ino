#include <Servo.h>
Servo duoji;

void setup() {
  duoji.attach(9);

}

void loop() {
  duoji.write(map(analogRead(A0),0,1023,0,180));//舵机写入角度为模拟读取的A0脚映射为0-1023为0-180
}
