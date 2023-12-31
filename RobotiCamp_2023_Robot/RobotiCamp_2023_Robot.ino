/*
   Titre  : RobotiCamp_2023_Robot
   Auteur : Frédéric Druppel
   Date   : 2023-08-02
   Link   : https://github.com/fred-corp/ESC_Robotic_Camp_2023
   Link 2 : https://bit.ly/ESC_Robotic


   Initialisation (setup) :
   1. Définir les E/S
   2. Regarder droit devant
   3. Délai avant de commencer les tâches

   Tâches (loop) :
   1. Le robot doit avancer en ligne droite
   2. Si il y a un obstacle :
     2.0 : Reculer un peu (optionnel)
     2.1 : Le robot s'arrête
     2.2 : Regarder le dégagement à gauche
     2.3 : Regarder le dégagement à droite
     2.4 : Tourner dans le sens où il y a le plus de dégagement
   3. Recommencer au point 1

*/

#include <Servo.h>
#include <SoftwareSerial.h>

// Motor driver pins
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 11

// Distance sensor pins
#define TRIG 7
#define ECHO 8

#define servoPin 4

// SoftwareSerial
#define txPin 9      // -> RX BlueTooth module
#define rxPin 10     // -> TX BlueTooth module

// Others
#define LED 13


Servo myservo;

SoftwareSerial bluetooth(rxPin, txPin);

// Calibration
const int forwardLeft   = 255;
const int forwardRight  = 255;
const int backwardLeft  = 255;
const int backwardRight = 255;

boolean autoMode = true;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(txPin, OUTPUT);
  pinMode(rxPin, INPUT);

  pinMode(LED, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(88);

  bluetooth.begin(9600);
  Serial.begin(9600);
  delay(2500);
}

void loop() {
  digitalWrite(LED, autoMode);
  
  if (autoMode) {
    autoPilot();
  }

  if (bluetooth.available()) {
    char received = bluetooth.read();
    Serial.println(received);

    switch (received) {
      case 'M':
        autoMode = !autoMode;
        break;
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        MStop();
        break;
    }
  }
}

void autoPilot() {
  if (distanceSensor() < 15) {
    backward();
    delay(600);

    MStop();
    delay(300);



    lookLeft();
    float distanceLeft = distanceSensor();
    delay(100);

    lookRight();
    float distanceRight = distanceSensor();
    delay(100);

    lookForward();

    if (distanceLeft > distanceRight) {
      left();
      delay(750);
    } else {
      right();
      delay(750);
    }

  }
  else {
    forward();
  }
}

void lookLeft() {
  myservo.write(180);
  delay(200);
}

void lookRight() {
  myservo.write(0);
  delay(200);
}

void lookForward() {
  myservo.write(88);
  delay(200);
}

void forward() {
  M1Move(0, forwardLeft);
  M2Move(0, forwardRight);
}

void backward() {
  M1Move(backwardLeft, 0);
  M2Move(backwardRight, 0);
}

void left() {
  M1Move(0, 0);
  M2Move(0, forwardRight);
}

void right() {
  M1Move(0, forwardLeft);
  M2Move(0, 0);
}

void MStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void M1Move(int speed1, int speed2) {
  analogWrite(IN1, speed1);
  analogWrite(IN2, speed2);
}

void M2Move(int speed3, int speed4) {
  analogWrite(IN3, speed3);
  analogWrite(IN4, speed4);
}

float distanceSensor() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(10);

  int time = pulseIn(ECHO, HIGH);

  float distance = ((time * 340.0) / 2.0) / 10000;

  return distance;
}

