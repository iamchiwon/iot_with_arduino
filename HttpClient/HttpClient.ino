#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoHttpClient.h>

char ssid[] = "SK_WiFiGIGA5F19";  //  your network SSID (name)
char pass[] = "1509003823";       // your network password

const char http_site[] = "www.naver.com";
const int http_port = 80;

WiFiClient client;
HttpClient httpClient = HttpClient(client, http_site, http_port);

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
}

void loop()
{
  httpClient.get("/");
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Finished Thing GET test");
  while(true){
    delay(1000);
  }
}

