import processing.serial.*;

int lf = 10;
float zoom = 0.1;
Serial serial;
PImage img;

void setup() {
  size(800, 600);
  img = loadImage("image.jpg");
  serial = new Serial(this, Serial.list()[1], 9600);
}


void draw() {
  background(0);

  if(serial.available() > 0) {
    String val = serial.readStringUntil(lf);
    if(val != null) {
      val = val.trim();
      if(val.length() > 0) {
        float val2 = Float.parseFloat(val.trim());
        zoom = max(min(val2 / 100, 1.0), 0.1);
      }
    }
  }
  
  float imageWidth = img.width * zoom;
  float imageHeight = img.height * zoom;
  image(img, (800 - imageWidth)/2, (600 - imageHeight)/2, imageWidth, imageHeight);
}