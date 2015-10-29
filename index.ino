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
    int colorLevel = n/12; //find the color
    int colors[3];
    if (colorLevel<1) {
        int colors[] = {0, 0, 255}; // [r, g, b]
    } else if (colorLevel < 2 && colorLevel >= 1) {
        int colors[] = {255, 0, 255}; // [r, g, b]
    } else if (colorLevel < 3 && colorLevel >= 2) {
        int colors[] = {0, 0, 255}; // [r, g, b]
    } else {
        int colors[] = {0, 0, 255};
    }
    for(int i = 0; i < level; i++) {
        strip.setPixelColor(i, strip.Color(colors[0], colors[1], colors[2]));
    }
    strip.show();
    return 1;
}

int updateLogos(String command) {
    int n = command.toInt(); //find amount of things tweeted in
    int level = n%12; //find the actual amount of LEDs to light
    int colorLevel = n/12; //find the color
    int colors[3];
    if (colorLevel<1) {
        int colors[] = {0, 255, 0}; // [r, g, b]
    } else if (colorLevel < 2 && colorLevel >= 1) {
        int colors[] = {255, 255, 0}; // [r, g, b]
    } else if (colorLevel < 3 && colorLevel >= 2) {
        int colors[] = {0, 255, 0}; // [r, g, b]
    } else {
        int colors[] = {0, 255, 0};
    }
    for(int i = 0; i > 11-level; i--) { //count backwards from level (11 is the total amount of LED's on the ring)
        strip.setPixelColor(i, strip.Color(colors[0], colors[1], colors[2]));
    }
    strip.show();
    return 1;
}

int updatePowerBar(String command) {
    int n = command.toInt(); //find amount of things tweeted in
    int level = n%24; //find the actual amount of LEDs to light
    int colorLevel = n/24; //find the color
    int colors[3];
    if (colorLevel<1) {
        int colors[] = {255, 0, 0}; // [r, g, b]
    } else if (colorLevel < 2 && colorLevel >= 1) {
        int colors[] = {122, 122, 122}; // [r, g, b]
    } else if (colorLevel < 3 && colorLevel >= 2) {
        int colors[] = {255, 255, 255}; // [r, g, b]
    } else {
        int colors[] = {255, 255, 255};
    }
    for(int i = 0; i < level; i++) { //count backwards from level (11 is the total amount of LED's on the ring)
        strip.setPixelColor(i, strip.Color(colors[0], colors[1], colors[2]));
    }
    strip.show();
    return 1;
}

int solidLights(int redValue, int blueValue, int greenValue) {
   //strip.Color(redValue, greenValue, blueValue)
   uint16_t i, j;
   for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(redValue, greenValue, blueValue));
    }
    strip.show();
    return 1;
}

int mailjetLight() {
    // int mailjetOrange[] = {255, 191, 64};
    // int mailjetBlueGrey[] = {238, 237, 243};
    // int mailjetLightBlack[] = {41, 44, 51};
    // int mailjetLightGrey[] = {230, 230, 230};
    // int mailjetWhite[] = {52, 152, 219};
    uint16_t i, j;
    int lightArray[2][3] = {{255, 204, 0}, {238, 237, 243}};
    int lightValueForArray = 0;
    for(i=0; i<strip.numPixels(); i++) {
      if(lightValueForArray > (sizeof(lightArray)/(3*sizeof(int)) - 1)) lightValueForArray = 0; //lightValueForArray > 1 where 1 is number of colors in array minus 1
      strip.setPixelColor(i, strip.Color(lightArray[lightValueForArray][0], lightArray[lightValueForArray][1], lightArray[lightValueForArray][2]));
      lightValueForArray += 1;
    }
    strip.show();
    return 1;
}

int christmasLight() {
    // int mailjetOrange[] = {255, 191, 64};
    // int mailjetBlueGrey[] = {238, 237, 243};
    // int mailjetLightBlack[] = {41, 44, 51};
    // int mailjetLightGrey[] = {230, 230, 230};
    // int mailjetWhite[] = {52, 152, 219};
    uint16_t i, j;
    int lightArray[2][3] = {{255, 0, 0}, {0, 255, 0}};
    int lightValueForArray = 0;
    for(i=0; i<strip.numPixels(); i++) {
      if(lightValueForArray > (sizeof(lightArray)/(3*sizeof(int)) - 1)) lightValueForArray = 0; //lightValueForArray > 1 where 1 is number of colors in array minus 1
      strip.setPixelColor(i, strip.Color(lightArray[lightValueForArray][0], lightArray[lightValueForArray][1], lightArray[lightValueForArray][2]));
      lightValueForArray += 1;
    }
    strip.show();
    return 1;
}
