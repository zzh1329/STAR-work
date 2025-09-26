#include <Servo.h>
Servo duoji;

void setup() {
  duoji.attach(8);

}

void loop() {
  duoji.write(0);
  delay(2000);
  duoji.write(30);
  delay(2000);
  duoji.write(45);
  delay(2000);
  duoji.write(90);
  delay(2000);
  duoji.write(135);
  delay(2000);
}