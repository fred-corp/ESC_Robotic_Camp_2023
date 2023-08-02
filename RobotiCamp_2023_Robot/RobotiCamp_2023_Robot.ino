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

// Motor driver pins
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 11

// Distance sensor pins
#define TRIG 7
#define ECHO 8

#define servoPin 4

Servo monservo;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  monservo.attach(servoPin);
  monservo.write(88);

  delay(2500);
}

void loop() {
  if (capteurDistance() < 15) {
    MStop();
    delay(500);
    
    lookLeft();
    float distanceLeft = capteurDistance();
    delay(100);
    
    lookRight();
    float distanceRight = capteurDistance();
    delay(100);

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
  monservo.write(180);
  delay(200);
}

void lookRight() {
  monservo.write(0);
  delay(200);
}

void forward() {
  M1Move(0, 255);
  M2Move(0, 255);
}

void backward() {
  M1Move(255, 0);
  M2Move(255, 0);
}

void left() {
  M1Move(0, 255);
  M2Move(0, 0);
}

void right() {
  M1Move(0, 0);
  M2Move(0, 255);
}

void MStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void M1Move(int vitesse1, int vitesse2) {
  analogWrite(IN1, vitesse1);
  analogWrite(IN2, vitesse2);
}

void M2Move(int vitesse3, int vitesse4) {
  analogWrite(IN3, vitesse3);
  analogWrite(IN4, vitesse4);
}

float capteurDistance() {
  // Activer le capteur
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(10);

  // Mesurer l'impulsion d'ECHO
  int temps = pulseIn(ECHO, HIGH);

  // Calculer la distance
  float distance = ((temps * 340.0) / 2.0) / 10000;

  // Renvoyer la valeur
  return distance;
}
