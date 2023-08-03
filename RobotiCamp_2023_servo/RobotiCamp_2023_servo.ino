#include <Servo.h>

#define servoPin 4

Servo myservo;

void setup() {
  myservo.attach(servoPin);
}

void loop() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
  myservo.write(180);
  delay(500);
}
