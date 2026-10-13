#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;

long duration;
int distance;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(12);
  
  // Opcional: limita a velocidade máxima do servo (ajuda bastante no SG90)
  myServo.write(15);   // posição inicial
  delay(500);
}

void loop() {
  // Ida: 15 → 165
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(50);                    // ← valor mais suave
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  // Volta: 165 → 15
  for (int i = 165; i >= 15; i--) {
    myServo.write(i);
    delay(50);                    // ← mesmo valor
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 30000); // timeout de 30ms (evita travamentos)
  distance = duration * 0.034 / 2;
  
  if (distance == 0 || distance > 400) distance = 400; // protege valores absurdos
  
  return distance;
}