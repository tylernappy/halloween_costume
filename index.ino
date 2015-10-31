#include <string.h>
#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 48
#define PIXEL_TYPE WS2812B

int faceIndex = 0;
int logoIndex = 0;
int powerBarIndex = 0;

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
    int red;
    int green;
    int blue;
    float oldColorLevel;
    float newColorLevel;
    while(faceIndex < n) {
        int led = faceIndex%12; //which LED to light up
        newColorLevel = (float)faceIndex/12.0; //which color to set the LED to
        int difference = (int)newColorLevel - (int)oldColorLevel;
        if (difference > 0 ){
            resetLEDsUp(0, 12); //run function to reset lights
        }
        //
        if (newColorLevel<1) {
            red = 0;
            green = 0;
            blue = 255;
        } else if (newColorLevel < 2 && newColorLevel >= 1) {
            red = 255;
            green = 0;
            blue = 255;
        } else if (newColorLevel < 3 && newColorLevel >= 2) {
            red = 255;
            green = 0;
            blue = 0;
        } else {
            red = 255;
            green = 0;
            blue = 0;
        }
        strip.setPixelColor(led, strip.Color(red, green, blue));
        faceIndex++;
        oldColorLevel = newColorLevel;
    }
    Serial.println("Faces ---------");
    Serial.print("n: ");
    Serial.println(n);
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
    int red;
    int green;
    int blue;
    float oldColorLevel;
    float newColorLevel;
    while(logoIndex < n) {
        int ledUnMapped = logoIndex%12; //which LED to light up
        int led = map(ledUnMapped, 0, 11, 23, 12);
        newColorLevel = (float)logoIndex/12.0; //which color to set the LED to
        int difference = (int)newColorLevel - (int)oldColorLevel;
        if (difference > 0 ){
            resetLEDsDown(24, 11); //run function to reset lights
        }
        //
        if (newColorLevel<1) {
            red = 0;
            green = 255;
            blue = 255;
        } else if (newColorLevel < 2 && newColorLevel >= 1) {
            red = 0;
            green = 255;
            blue = 0;
        } else if (newColorLevel < 3 && newColorLevel >= 2) {
            red = 0;
            green = 0;
            blue = 255;
        } else {
            red = 0;
            green = 0;
            blue = 255;
        }
        strip.setPixelColor(led, strip.Color(red, green, blue));
        logoIndex++;
        oldColorLevel = newColorLevel;
    }
    Serial.println("Faces ---------");
    Serial.print("n: ");
    Serial.println(n);
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
    int red;
    int green;
    int blue;
    float oldColorLevel;
    float newColorLevel;
    while(powerBarIndex < n) {
        int led = (powerBarIndex%24) + 24; //which LED to light up
        newColorLevel = (float)powerBarIndex/24.0; //which color to set the LED to
        int difference = (int)newColorLevel - (int)oldColorLevel;
        if (difference > 0 ){
            resetLEDsUp(24, 48); //run function to reset lights
        }
        //
        if (newColorLevel<1) {
            red = 255;
            green = 0;
            blue = 0;
        } else if (newColorLevel < 2 && newColorLevel >= 1) {
            red = 122;
            green = 122;
            blue = 122;
        } else if (newColorLevel < 3 && newColorLevel >= 2) {
            red = 255;
            green = 0;
            blue = 255;
        } else {
            red = 255;
            green = 0;
            blue = 255;
        }
        strip.setPixelColor(led, strip.Color(red, green, blue));
        powerBarIndex++;
        oldColorLevel = newColorLevel;
    }
    Serial.println("Faces ---------");
    Serial.print("n: ");
    Serial.println(n);
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

void resetLEDsUp(int start, int stop) {
   for(int i = start; i < stop; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}

void resetLEDsDown(int start, int stop) {
   for(int i = start; i > stop; i--) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}

int solidLights(int redValue, int blueValue, int greenValue) {
   uint16_t i, j;
   for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(redValue, greenValue, blueValue));
    }
    strip.show();
    return 1;
}
