#include <Arduino.h>


int trig = 9;
int echo = 10;
int red = 4;
int yellow = 5;
int green = 6;
int blue = 7;
int buzzer = 8;

long duration;
int distance;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 40) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    noTone(buzzer);
  }
  else if (distance <= 40 && distance > 30) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    tone(buzzer, 200);
  }
  else if (distance <= 30 && distance > 20) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    tone(buzzer, 400);
  }
  else if (distance <= 20 && distance > 10) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    tone(buzzer, 600);
  }
  else if (distance <= 10) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    tone(buzzer, 1000);
  }
  
  delay(100);
}