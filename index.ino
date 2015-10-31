#include <string.h>
#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 48
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up...");

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  initialize();

  Spark.function("sendFaces", updateFaces);
  Spark.function("sendLogos", updateLogos);
  Spark.function("sendPowerBar", updatePowerBar);
}

void loop() {
    delay(20);
}

void initialize() {
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    strip.show();
    delay(2000);
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(2000);
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    strip.show();
    delay(2000);
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(30);
}

//SparkCoreFunction
int updateFaces(String command) {
    int n = command.toInt(); //find amount of things tweeted in
    int level = n%12; //find the actual amount of LEDs to light
    float colorLevel = (float)n/12.0; //find the color
    int red;
    int green;
    int blue;
    if (colorLevel<1) {
        red = 0;
        green = 0;
        blue = 255;
    } else if (colorLevel < 2 && colorLevel >= 1) {
        red = 255;
        green = 0;
        blue = 255;
    } else if (colorLevel < 3 && colorLevel >= 2) {
        red = 255;
        green = 0;
        blue = 0;
    } else {
        red = 255;
        green = 0;
        blue = 0;
    }

    for(int i = 0; i < level; i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    Serial.println("Faces ---------");
    Serial.print("n: ");
    Serial.println(n);
    Serial.print("level: ");
    Serial.println(level);
    Serial.print("colorLevel: ");
    Serial.println(colorLevel);
    Serial.print("red: ");
    Serial.print(red);
    Serial.print(", green: ");
    Serial.print(green);
    Serial.print(", blue: ");
    Serial.println(blue);

    strip.show();
    delay(40);
    return 1;
}

int updateLogos(String command) {
    int n = command.toInt(); //find amount of things tweeted in
    int level = n%12; //find the actual amount of LEDs to light
    float colorLevel = (float)n/12.0; //find the color
    int red;
    int green;
    int blue;
    if (colorLevel<1) {
        red = 0;
        green = 255;
        blue = 0;
    } else if (colorLevel < 2 && colorLevel >= 1) {
        red = 0;
        green = 255;
        blue = 255;
    } else if (colorLevel < 3 && colorLevel >= 2) {
        red = 0;
        green = 0;
        blue = 255;
    } else {
        red = 0;
        green = 0;
        blue = 255;
    }
    for(int i = 23; i > 23-level; i--) { //count backwards from level (11 is the total amount of LED's on the ring)
        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    Serial.println("Logos ---------");
    Serial.print("n: ");
    Serial.println(n);
    Serial.print("level: ");
    Serial.println(level);
    Serial.print("colorLevel: ");
    Serial.println(colorLevel);
    Serial.print("red: ");
    Serial.print(red);
    Serial.print(", green: ");
    Serial.print(green);
    Serial.print(", blue: ");
    Serial.println(blue);

    strip.show();
    delay(40);
    return 1;
}

int updatePowerBar(String command) {
    int n = command.toInt(); //find amount of things tweeted in
    int level = n%24; //find the actual amount of LEDs to light
    float colorLevel = (float)n/24.0; //find the color
    int red;
    int green;
    int blue;
    if (colorLevel<1) {
        red = 255;
        green = 0;
        blue = 0;
    } else if (colorLevel < 2 && colorLevel >= 1) {
        red = 122;
        green = 122;
        blue = 122;
    } else if (colorLevel < 3 && colorLevel >= 2) {
        red = 255;
        green = 0;
        blue = 255;
    } else {
        red = 255;
        green = 0;
        blue = 255;
    }
    for(int i = 24; i < (level + 24); i++) { //count backwards from level (11 is the total amount of LED's on the ring)
        strip.setPixelColor(i, strip.Color(red, green, blue));
    }


    Serial.println("Power Bar ---------");
    Serial.print("n: ");
    Serial.println(n);
    Serial.print("level: ");
    Serial.println(level);
    Serial.print("colorLevel: ");
    Serial.println(colorLevel);
    Serial.print("red: ");
    Serial.print(red);
    Serial.print(", green: ");
    Serial.print(green);
    Serial.print(", blue: ");
    Serial.println(blue);

    strip.show();
    delay(40);
    return 1;
}

int solidLights(int redValue, int blueValue, int greenValue) {
   uint16_t i, j;
   for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(redValue, greenValue, blueValue));
    }
    strip.show();
    return 1;
}
