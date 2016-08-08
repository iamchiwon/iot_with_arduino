#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>

int pinDHT11 = 2;
int pinRelay = 7;
int pinLED = 13;

SimpleDHT11 dht11;
LiquidCrystal_I2C lcd(0x27,16,2);  //LCD address : 0x27

void setup() {
  Serial.begin(9600);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLED, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("No Data");
    delay(1000);
    return;
  }

  //temporary
  lcd.setCursor(0, 0);
  lcd.print("Temp  ");
  lcd.print((int)temperature);
  lcd.print(" *C");

  //humidity
  lcd.setCursor(0, 1);
  lcd.print("Hum   ");
  lcd.print((int)humidity);
  lcd.print(" %");

  //control fan
  if(temperature > 28) {
    digitalWrite(pinRelay, HIGH);
    digitalWrite(pinLED, HIGH);
    Serial.println("fan On");
  } else {
    digitalWrite(pinRelay, LOW);
    digitalWrite(pinLED, LOW);
    Serial.println("fan Off");
  }

  delay(3*1000);
}
