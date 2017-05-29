//	Arduino Program for Running Strip LEDs via Pi Webserver
const int BAUD_RATE = 9600;

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9
#define NUM_LEDS 240

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

uint32_t input = 4278190080; //WHITE
uint32_t previousInput = input;

void setup() {
  
  Serial.begin(BAUD_RATE);
//  attach_callbacks();    
  Serial.println("White is Up");
  strip.begin();
  colorWipe(input); //WHITE
}

void loop() {

  if(Serial.available()>0){
    previousInput = input;
    input = Serial.parseInt();
    colorWipe(input); //WHITE
  }
}

void colorWipe(uint32_t color) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
  Serial.println(color);
  Serial.println("Complete");
}

