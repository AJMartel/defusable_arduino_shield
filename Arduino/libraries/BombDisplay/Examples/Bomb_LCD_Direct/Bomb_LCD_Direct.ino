/*
     This is an example to use the bomb display without the library
     J.A. Korten
     April 17, 2017

     Example for the use of the BombDisplay without the Library

     Defusable Alarm Clock - www.jksoftedu.nl

     The Defusable Alarm Clock uses a:
     4 digits 7-segment display with four decimal points, a colon and apostrophe
     common anode
     HT16K33 address (standard with solderjumpers open): 0x73
*/

#include <Wire.h>
// we don't use #include <BombDisplay.h>

const int i2c_addr = 0x73;

//BombDisplay bombDisplay = BombDisplay(0x73);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  initDisplay();
  setBlinkRate();
  setBrightness(); 
  
  writeZeros();
}

void loop() {
  // do nothing
}

void writeZeros() {
  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)0x00); // start at address $00

  // first three digits are not connected to the HT16K33
  Wire.write(0x00); // n/a
  Wire.write(0x00); // n/a

  Wire.write(0x00); // n/a
  Wire.write(0x00); // n/a

  Wire.write(0x00); // n/a
  Wire.write(0x00); // n/a

  // most left digit
  Wire.write(0b11100000);
  Wire.write(0b00000111);

  // second digit from the left
  Wire.write(0b11100000);
  Wire.write(0b00000111);

  // second digit from the right
  Wire.write(0b11100000);
  Wire.write(0b00000111);

  // most right digit
  Wire.write(0b11100000);
  Wire.write(0b00000111);

  // there is potentially still one digit but it is not connected to the HT16K33
  Wire.endTransmission();
}

void initDisplay() {
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21); // turn on oscillator
  Wire.endTransmission();


  delay(100);

}

void setBlinkRate() {
  // Blink rate:
  Wire.beginTransmission(i2c_addr);
  int blinkrate = 4;
  if (blinkrate > 3) blinkrate = 0; // turn off if not sure
  Wire.write(0x80 | 0x01 | (blinkrate << 1));
  Wire.endTransmission();

}

void setBrightness() {
  // brightness
  int brightness = 15;

  if (brightness > 15) brightness = 15;
  Wire.beginTransmission(i2c_addr);
  Wire.write(0xE0 | brightness);
  Wire.endTransmission();
}

