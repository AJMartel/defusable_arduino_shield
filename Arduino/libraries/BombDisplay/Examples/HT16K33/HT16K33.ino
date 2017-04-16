/*  
 *   This is a library for the HT16K33
 *   J.A. Korten
 *   April 7, 2017
 *   
 *   Example for the use of the BombDisplay Library
 *   
 *   Defusable Alarm Clock - www.jksoftedu.nl 
 *   
 *   The Defusable Alarm Clock uses a:
 *   4 digits 7-segment display with four decimal points, a colon and apostrophe
 *   common anode
 *   HT16K33 address (standard with solderjumpers open): 0x73
 */

#include <Wire.h>
#include <BombDisplay.h>

BombDisplay bombDisplay = BombDisplay(0x73);

int output = 0;
boolean colon = false;
boolean _apostrophe = true;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bombDisplay.initDisplay();
}

void loop() {
  int k = 0;
  
  for (int i = 0; i <= 24; i++) {
    bombDisplay.setHours(i);
    for (int j = 0; j <= 59; j++) {
      bombDisplay.setMinutes(j);
      delay(50);
      if (j % 10 == 0) {
        colon = !colon;
        bombDisplay.setColon(colon);
      }
    }
    bombDisplay.setComma(i, true);
    bombDisplay.setComma(i-1, false);
  }
  bombDisplay.setApostrophe(_apostrophe);
  _apostrophe = !_apostrophe;
}

