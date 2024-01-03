#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        0 // On Trinket or Gemma, suggest changing this to 1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 6 // Popular NeoPixel ring size
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels


#include <tiny_IRremote.h>
#include <tiny_IRremoteInt.h>
int IRpin = 2;
IRrecv IR(IRpin);
decode_results results;


#include <SoftwareSerial.h>
#define RX    14   
#define TX    3 
SoftwareSerial mySerial (RX, TX);

int xi = 1;


void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 
  IR.enableIRIn();
  mySerial.begin(9600);
}

 
  uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
   

void loop() {

  if(xi == 1)
  {
    uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(3);
  }
   xi = 0;
  }

  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show(); 
  while (IR.decode(&results) == 0) {

      
  }

  mySerial.print("Value:");
  mySerial.println(IR.decode(&results));


  
  if (results.value == 0xFFA25D) {
    pixels.clear(); // Set all pixel colors to 'off'
    delay(50);
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }
  delay(2000);
  xi = 1;
 
  }

   if (results.value == 0xFF629D) {
    pixels.clear(); // Set all pixel colors to 'off'
    delay(50);
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }
  delay(2000);
  xi = 1;
  }

  if (results.value == 0xFFE21D) {
    pixels.clear(); // Set all pixel colors to 'off'
    delay(50);
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }
  delay(2000);
  xi = 1;
  }
 
  delay(50);
  IR.resume();
}
