#define TRIG 7
#define ECHO 8


void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.begin(9600);
}

void loop() {
  float distance = distanceSensor();
  
  // Show distance on console
  Serial.println(distance);
}

float capteurDistance() {
  // Trigger sensor
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(10);

  // Measure ECHO duration
  int time = pulseIn(ECHO, HIGH);

  // Calculate distance
  float distance = ((time * 340.0 / 10000) / 2.0);

  // Return distance value
  return distance;
}
