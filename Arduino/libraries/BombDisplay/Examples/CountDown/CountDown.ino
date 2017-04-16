/*
     This is a RealTime Clock Example
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
     This example counts down from 9999 .. 0
*/

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>
#include <BombDisplay.h>

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

unsigned long secTimer = 0;
unsigned long colonBlinker = 0;
boolean _colon = false;
BombDisplay bombDisplay = BombDisplay(0x73);

int countDown = 1234;


void setup () {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);
  Wire.begin();
  bombDisplay.initDisplay();

  delay(1000); // wait for console opening

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC :(");
    while (1);
  }

  if (rtc.lostPower()) {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    //      April 7, 2017 at 10:06 pm you would call:
    // rtc.adjust(DateTime(2017, 4, 7, 22, 6, 0));

    Serial.println("RTC lost power, we did a time reset based on sketch!");
    Serial.println("Note: you can insert a battery in the small ");
    Serial.println("battery slot of the shield to preseve time");
  }
  bombDisplay.setBombTime(countDown);
  delay(5000); // delay for 5 seconds before counting down
}

void loop() {
  // put your main code here, to run repeatedly:
  updateDisplay(); // non interrupting timer.
}

void updateDisplay() {
  updateCountDown();
}

void updateCountDown() {
  if (millis() > (secTimer + 1000)) {
    secTimer = millis();
    countDown--;
    bombDisplay.setBombTime(countDown);
  }
}
