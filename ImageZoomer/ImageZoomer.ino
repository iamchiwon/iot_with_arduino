int pinTrig = 7;
int pinEcho = 6;

void setup() {
  Serial.begin(9600);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop() {
  int value = distance();
  Serial.println(value);
  delay(300);
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
