/*
     This is an extensive example with almost all options for the Defusable Alarm Clock present/

     for use with the library for the HT16K33 / 7 Segment Display
     and the RTC chip (DS3231)

     Requires: https://github.com/adafruit/RTClib

     J.A. Korten
     April 7, 2017
     V1.0

     Example for the use of the BombDisplay Library

     Defusable Alarm Clock - www.jksoftedu.nl

     The Defusable Alarm Clock uses a:
     4 digits 7-segment display with four decimal points, a colon and apostrophe
     common anode
     HT16K33 address (standard with solderjumpers open): 0x73

     See RT_Clock for the normal alarm clock mode
     See also the other examples.
*/

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>
#include <BombDisplay.h>

RTC_DS3231 rtc;

boolean _colon = false;
BombDisplay bombDisplay = BombDisplay(0x73);

int countDown = 1234;
int updateSpeed = 1000; // 1000 for update per second, 100 for update per millisecond
boolean useSoundFeedback = false;
unsigned long startCountDown = 0;
int shakeDelay = 5000; // default
boolean countingDown = false;

void setup () {
  setupLeds();
  setArmed(false);
  setupSerial();
  setupDisplay();
  setupRTC();
  setupButtons();
  setupBombWires();
  setupShaker();

  bombDisplay.setBombTime(countDown);
  while (!checkButtonA()); // wait till button A was pressed
  setArmed(true);
  startCountDown = millis();
  updateShakerState(5000);
  countingDown = true;
}

void loop() {
  // put your main code here, to run repeatedly:

  updateButtonStates();
  if (countingDown) {
    doCountDown();
  }
}

// All kinds of methods

/* Setup methods: */

void setupSerial() {
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);
}

void setupDisplay() {
  Wire.begin();
  bombDisplay.initDisplay();
}


void doCountDown() {
  updateDisplay(); // non interrupting timer.
  if (millis() > (startCountDown + shakeDelay)) {
    updateShaker(); // read Tilt sensor
  } else {
    updateShakerState(shakeDelay);
  }
}




