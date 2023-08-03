#include <SoftwareSerial.h>

#define txPin 9      // -> RX BlueTooth module
#define rxPin 10     // -> TX BlueTooth module

#define led 13

SoftwareSerial bluetooth(rxPin, txPin);

void setup() {
  pinMode(txPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(led, OUTPUT);

  bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    char received = bluetooth.read();

    switch (received) {
      case '1' :
        digitalWrite(led, HIGH);
        break;
      case '2' :
        digitalWrite(led, LOW);
        break;
      default :
        Serial.print("Commande non reconnue : ");
        Serial.println(received);
        break;
    }
  }
}



