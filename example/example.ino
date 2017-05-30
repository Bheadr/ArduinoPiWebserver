//	Arduino Program for Running Strip LEDs via Pi Webserver
const int BAUD_RATE = 9600;

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9
#define NUM_LEDS 240
#define BRIGHTNESS 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

uint8_t input0 = 0; //RED
uint8_t input1 = 0; //GREEN
uint8_t input2 = 0; //BLUE
uint8_t input3 = 0; //WHITE

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("White is Up");
  strip.begin();
  colorWipe(strip.Color(input0,input1,input2,input3));
}

void loop() {

  if(Serial.available()>=4){
    input0 = Serial.read();
    input1 = Serial.read();
    input2 = Serial.read();
    input3 = Serial.read();    
    colorWipe(strip.Color(input0,input1,input2,input3)); //WHITE
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

