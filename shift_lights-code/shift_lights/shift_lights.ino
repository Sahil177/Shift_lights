//initialize libraries
#include <Adafruit_NeoPixel.h>

#define PIN            6  //LED Data Pin
#define NUMPIXELS      19  //number of leds connected
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const unsigned int minRPM = 3700; // Minimum RPM before lights turn on
const unsigned int maxRPM = 7050; // Max RPM in normal operating range
const unsigned int shiftRPM = 7500; // uper limit between where the shift should occur ie shift between 7050 and 7500
const unsigned int mintemp = 35; // minimum coolant temperature
const unsigned int maxtemp = 100; // max safe coolant temperature
const unsigned int warningtemp = 107; // warning temp

//Defining the colours for the RPM pixels
const uint32_t pixcolour[15] = {
  Adafruit_NeoPixel::Color(0, 120, 0),
  Adafruit_NeoPixel::Color(0, 120, 0),
  Adafruit_NeoPixel::Color(0, 120, 0),
  Adafruit_NeoPixel::Color(15, 105, 0),
  Adafruit_NeoPixel::Color(30, 90, 0),
  Adafruit_NeoPixel::Color(45, 75, 0),
  Adafruit_NeoPixel::Color(60, 60, 0),
  Adafruit_NeoPixel::Color(75, 45, 0),
  Adafruit_NeoPixel::Color(90, 30, 0),
  Adafruit_NeoPixel::Color(105, 15, 0),
  Adafruit_NeoPixel::Color(120, 0, 0),
  Adafruit_NeoPixel::Color(0, 0, 120),
  Adafruit_NeoPixel::Color(0, 0, 120),
  Adafruit_NeoPixel::Color(0, 0, 120),
  Adafruit_NeoPixel::Color(0, 0, 120),
  
};

const unsigned int lightShiftRPM[NUMPIXELS] = {
  minRPM,
  3923,
  4146,
  4369,
  4592,
  4815,
  5038,
  5261,
  5484,
  5707,
  5930,
  6153,
  6376,
  6599,
  6822,
}; // this defines the ranges for which nixeopixel will light within. These can be change to be vary non-linearly

int i;
float rpm;
float clt;

void setup() {
  pixels.begin(); // initialize neopixels
}

void loop() {
  //rpm = 3600 + 3.74*analogRead(0); for testing purposes(potentiometer)
  //clt = 30+ 0.08*analogRead(1); for testing purposes
  if (rpm >= minRPM && rpm < maxRPM){
    // normal operating range
    for (int i =2; i < 17; ++i){
      if (rpm > lightShiftRPM[i-2] ){
        pixels.setPixelColor(i, pixcolour[i-2]);
      }
      else {
        pixels.setPixelColor(i, pixels.Color(0,0,0));
      }
  }
    pixels.show();
  }
  else if (rpm >= maxRPM && rpm < shiftRPM){
    //shift flash
    //blue flash
        pixels.fill(pixels.Color(0, 0, 120));
    pixels.show();
    delay(20);
    pixels.fill(pixels.Color(0, 0, 0));
    pixels.show();
    delay(20);
  }
  else if (rpm >= shiftRPM) {
    //overev flash
    //red
    pixels.fill(pixels.Color(120, 0, 0));
    pixels.show();
    delay(20);
    pixels.fill(pixels.Color(0, 0, 0));
    pixels.show();
    delay(20);
  }
  else if (rpm <= minRPM){
    for( i=2; i < 17; ++i){
      pixels.setPixelColor(i, pixels.Color(0,0,0));
    }
    pixels.show();
  }
      
  if (clt < mintemp) {
    pixels.setPixelColor(0, pixels.Color(0,0,200));
    pixels.setPixelColor(1, pixels.Color(0,0,200));
    pixels.setPixelColor(17, pixels.Color(0,0,200));
    pixels.setPixelColor(18, pixels.Color(0,0,200));
    pixels.show();
  }
  else if ( clt >= mintemp && clt < maxtemp){
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(17, pixels.Color(0,0,0));
    pixels.setPixelColor(18, pixels.Color(0,0,0));
    pixels.show();
  }
  else if (clt >= maxtemp && clt < warningtemp){
    pixels.setPixelColor(0, pixels.Color(200,0,0));
    pixels.setPixelColor(1, pixels.Color(200,0,0));
    pixels.setPixelColor(17, pixels.Color(200,0,0));
    pixels.setPixelColor(18, pixels.Color(200,0,0));
    pixels.show();
  }
  else if (clt >= warningtemp) {
    pixels.setPixelColor(0, pixels.Color(200,0,0));
    pixels.setPixelColor(1, pixels.Color(200,0,0));
    pixels.setPixelColor(17, pixels.Color(200,0,0));
    pixels.setPixelColor(18, pixels.Color(200,0,0));
    pixels.show();
    delay(20);
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(17, pixels.Color(0,0,0));
    pixels.setPixelColor(18, pixels.Color(0,0,0));
    pixels.show();
    delay(20);
  }
}
