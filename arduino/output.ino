//Made by Valery Smith 2018
//Hack ISUUU

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

int NUMPIXELS = 37; // Number of LEDs in strip

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
  Serial.begin(115200);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  for ( int j = 0; j <= NUMPIXELS + NUMPIXELS; ++j) {
    strip.setPixelColor(j, 0);
  } // 'Off' pixel at tail
  //strip.show();
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int hold;
int endLED = 0; // Index of the score/top pixel
uint32_t green = 0xFF0000;      // 'On' color (starts red)
uint32_t yelllow = 0xC36B13;
uint32_t blue = 0x0000FF;
uint32_t white = 0xB7AD39;
uint32_t red = 0x00FF00;
uint32_t purple = 0x6DAE4;
uint32_t color = 0x0000;
String inString = "";
void loop() {
  if (Serial.available() > 0) {

    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
       Serial.println(inChar);
    }
    // if you get a newline, then aset the endLED
    if (inChar == 13) {
      endLED = inString.toInt();
      // clear the string for new input:
      Serial.println(endLED);
      inString = "";
    }
  }

  for (int i = 1; i <= endLED; i++) {
    if (i < 12) {
      color = red;
    }
    if (i < 25 && i > 12) {
      color = yelllow;
    }
    if (i > 24 ) {
      color = blue;
    }
    strip.setPixelColor(i, color); // 'On' pixel at head}
  }
  for ( int j = endLED; j < NUMPIXELS; ++j) {
    strip.setPixelColor(j, 0);
  } // 'Off' pixels after the endLED
  strip.show();                     // Refresh strip
  delay(5);                        // Pause 20 milliseconds (~50 FPS)
}
