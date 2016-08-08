#include <Servo.h>

#define OPEN  180
#define CLOSE 0

int pinTrig = 7;
int pinEcho = 6;
int pinServo = 9;
int pinLed= 13;
int state = CLOSE;

Servo servo;

void setup() {
  servo.attach(pinServo);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  long val = distance();
  if(val < 100) {
    state = OPEN;
    digitalWrite(pinLed, HIGH);
  } else {
    state = CLOSE;
    digitalWrite(pinLed, LOW);
  }

  servo.write(state);

  if(state == OPEN) {
    delay(5*1000);
  } else {
    delay(500);
  }
}

long distance() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  long val= pulseIn(pinEcho, HIGH) * 17 / 100;
  return val;
}

