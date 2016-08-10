#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SimpleDHT.h>
#include <SimpleTimer.h>
#include "ThingSpeak.h"

char ssid[] = "SK_WiFiGIGA5F19";
char pass[] = "1509003823";
char ThingSpeakWriteApiKey[] = "FF98OKP2FL0764B2";
int ThingSpeakChannelNumber = 144236;

int pinDHT11 = D2;
SimpleDHT11 dht11;
SimpleTimer timer;
WiFiClient client;

void every5second() {
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.println("No Data");
  }
  else {
    ThingSpeak.writeField(ThingSpeakChannelNumber, 1, temperature, ThingSpeakWriteApiKey);
    ThingSpeak.writeField(ThingSpeakChannelNumber, 2, humidity, ThingSpeakWriteApiKey);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
  timer.setInterval(5000, every5second);
}

void loop()
{
  timer.run();
}

