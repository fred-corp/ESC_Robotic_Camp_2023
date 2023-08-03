// Motor driver pins
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 11

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  delay(2500);
}

void loop() {
  M1Move(0, 255);
  M2Move(0, 255);
  delay(1000);
  MStop();
  delay(1000);
}

void MStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Motor 1 Commands
void M1Move(int vitesse1, int vitesse2) {
  analogWrite(IN1, vitesse1);
  analogWrite(IN2, vitesse2);
}

// Motor 2 Commands
void M2Move(int vitesse3, int vitesse4) {
  analogWrite(IN3, vitesse3);
  analogWrite(IN4, vitesse4);
}
