// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 10 // Number of LEDs in strip
int NUMLEDS = 8;

int CURRENT_STATE = 0;
const int INITIAL_STATE = 0;
const int LOOP_COLOR = 1;
const int REVERSE_STATE = 2;
const int SPARKLE_STATE = 3;
const int CLEAR_LIGHTS_STATE = 4;

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -9; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)

void loop() {
  switch (CURRENT_STATE){
    case INITIAL_STATE:
    doInitialLight();
    break;
    case LOOP_COLOR:
    doLoopColor();
    break;
    case REVERSE_STATE:
    doReverseColor();
    break;
    case SPARKLE_STATE:
    doSparkleSparkle();
    break;
    case CLEAR_LIGHTS_STATE:
    doClearLights();
    break;
  }
}

void doInitialLight(){
  uint32_t color = doColor(255, 35,0); 
  for(int i = 0; i < NUMLEDS; i++){
    setLight(i, color);
delay(500);
  }
  CURRENT_STATE = LOOP_COLOR;
}

void doLoopColor(){
  long r = random(0, 255);
long g = random(0, 255);
long b = random(0, 255);

     uint32_t color = doColor(r, g,b); 
  for(int i = 0; i < NUMLEDS; i++){
    setLight(i, color);
    delay(50);
  }
  CURRENT_STATE = REVERSE_STATE; 
}

void doReverseColor(){
  long r = random(0, 255);
long g = random(0, 255);
long b = random(0, 255);

     uint32_t color = doColor(r, g,b); 
  for(int i = NUMLEDS; i > 0; i--){
    setLight(i, color);
    delay(50);
  }
  CURRENT_STATE = SPARKLE_STATE; 
}

void doSparkleSparkle(){
static int howManySparkles = 0;
long r = random(0, 255);
long g = random(0, 255);
long b = random(0, 255);

       uint32_t color = doColor(r, g,b); 
       long randNumber = random(0, NUMLEDS);
       setLight(NUMLEDS, doColor(255, 35,0));
 for(int i = 0; i < NUMLEDS-1; i++){
  if((i % randNumber == 0) && (i >0)){
    setLight(i, 0);
  }
  else{
    setLight(i, color);
  }
    delay(50);
  }

  
  if(howManySparkles >= 50){
    howManySparkles = 0;
    CURRENT_STATE = CLEAR_LIGHTS_STATE;
  }
  howManySparkles++;
}

void doClearLights(){
    for(int i = NUMLEDS; i > 0; i--){
    setLight(i, 0);
    delay(50);
  }
  CURRENT_STATE = INITIAL_STATE;
}
uint32_t doColor(int r, int g, int b){
  return ((long) g<<16) + ((long)r<<8) + b;
}
void setLight(int ledIndex, uint32_t ledColor){
  strip.setPixelColor(ledIndex, ledColor); // 'On' pixel at head
  strip.show();                     // Refresh strip
}


