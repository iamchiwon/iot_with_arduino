#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

#define SENSORDATA_JSON_SIZE (JSON_OBJECT_SIZE(500))

char ssid[] = "SK_WiFiGIGA5F19";
char pass[] = "1509003823";

const char http_site[] = "openapi.seoul.go.kr";
const int http_port = 8088;

WiFiClient client;
HttpClient httpClient = HttpClient(client, http_site, http_port);

LiquidCrystal_I2C lcd(0x27,16,2);  //LCD address : 0x27

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
  
  lcd.init();
  lcd.backlight();
}

void loop()
{
  httpClient.get("/sample/json/RealtimeCityAir/1/5/");
  int statusCode = httpClient.responseStatusCode();
  Serial.println(statusCode);
  if(statusCode == 200) {
    String response = httpClient.responseBody();

    StaticJsonBuffer<SENSORDATA_JSON_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(response);
    root.prettyPrintTo(Serial);
    
    if (root.success()) {
      JsonArray& rows = root["RealtimeCityAir"]["row"].asArray();
      int size = rows.size();
      
      JsonObject& row = rows.get(size-1); //last one
      float pm10 = row["PM10"]; //미세먼지
      float ppm = row["O3"]; //오존

      lcd.setCursor(0, 0);
      lcd.print("Dust:");
      lcd.print(pm10);
      lcd.print(" ug/m2");

      lcd.setCursor(0, 1);
      lcd.print(" O3 :");
      lcd.print(ppm);
      lcd.print(" ppm");
    }
  }

  delay(30*60*1000);
}

