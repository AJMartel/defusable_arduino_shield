/*
 *   This is a library for the HT16K33 / Defusable Alarm Clock
 *   J.A. Korten
 *   April 7, 2017
 *   Version 1.0
 *
 *   BombDisplay.h
 *
 *   Defusable Alarm Clock - www.jksoftedu.nl
 *
 *   Inspired by the HT16K33 library from Limor Fried/Ladyada/Adafruit Industries.
 *
 *   The Defusable Alarm Clock uses a:
 *   4 digits 7-segment display with four decimal points, a colon and apostrophe
 *   common anode
 *   HT16K33 address (standard with solderjumpers open): 0x73
 *
 *   MIT license, all text above must be included in any redistribution
 *   See the cpp file for more info.
 */

#ifndef BombDisplay_h
#define BombDisplay_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include <Wire.h>

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0

class BombDisplay {
  public:
    BombDisplay(uint8_t i2c_addr);
    void begin(uint8_t _addr);
    void clear(void);
    uint16_t displaybuffer[8];

    void init(uint8_t a);

    void initDisplay();
    void bombDisplayClear();
    void writeDisplay();
    void setBrightness(uint8_t b);
    void blinkRate(uint8_t b);

    void setTime(byte hours, byte minutes);
    void setHours(byte hours);
    void setMinutes(byte minutes);
    void setBombTime(int seconds);

    void setComma(byte comma, boolean on);
    void setColon(boolean on);
    void setApostrophe(boolean on);

  protected:

  private:
    void writeBuffer();

};

#endif
