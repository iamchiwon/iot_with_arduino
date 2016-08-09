#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char ssid[] = "SK_WiFiGIGA5F19";  //  your network SSID (name)
char pass[] = "1509003823";       // your network password

const char http_site[] = "www.naver.com";
const int http_port = 80;

WiFiClient client;

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
  if ( !getPage() ) {
    Serial.println("GET request failed");
  }
  
  while ( client.available() ) {
    char c = client.read();
    Serial.print(c);
  }

  if ( !client.connected() ) {
    Serial.println();
    
    client.stop();
    if ( WiFi.status() != WL_DISCONNECTED ) {
      WiFi.disconnect();
    }
    
    // Do nothing
    Serial.println("Finished Thing GET test");
    while(true){
      delay(1000);
    }
  }
}

bool getPage() {
  
  // Attempt to make a connection to the remote server
  if ( !client.connect(http_site, http_port) ) {
    return false;
  }
  
  // Make an HTTP GET request
  client.println("GET /index.html HTTP/1.1");
  client.print("Host: ");
  client.println(http_site);
  client.println("Connection: close");
  client.println();
  
  return true;
}
