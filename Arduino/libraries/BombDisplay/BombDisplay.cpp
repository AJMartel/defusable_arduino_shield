/*
 *   This is a library for the HT16K33
 *   J.A. Korten
 *   April 7, 2017
 *   Version 1.0
 *
 *   BombDisplay.cpp
 *
 *   Defusable Alarm Clock - www.jksoftedu.nl
 *
 *   Inspired by the HT16K33 library from Limor Fried/Ladyada/Adafruit Industries.
 *   MIT license, all text above must be included in any redistribution
 *
 *   The Defusable Alarm Clock uses a:
 *   4 digits 7-segment display with four decimal points, a colon and apostrophe
 *   common anode
 *   HT16K33 address (standard with solderjumpers open): 0x73
 */

#include <Wire.h>

#include "BombDisplay.h"

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

uint8_t i2c_addr = 0x73;

uint16_t commas[4] = {0, 0, 0, 0};
boolean apostrophe = false;

const uint16_t bombclocktable[15] = {
  0b0011111100000,
  0b0000011000000,
  0b0101101100000,
  0b0100111100000,
  0b0110011000000,
  0b0110110100000,
  0b0111110100000,
  0b0000011100000,
  0b0111111100000,
  0b0110111100000,
  0b1000000000000,
  0b0100000000000,
  0b0000000001000,
  0b0000000010000
};

// 0: 0b0011111100000
// 1: 0b0000011000000
// 2: 0b0101101100000
// 3: 0b0100111100000
// 4: 0b0110011000000
// 5: 0b0110110100000
// 6: 0b0111110100000
// 7: 0b0000011100000
// 8: 0b0111111100000
// 9: 0b0110111100000
// .: 0b1000000000000 dec. punt
// :: 0b0000000001000 colon    displaybuffer[1]
// ': 0b0000000010000 apostrof displaybuffer[2]


BombDisplay::BombDisplay(uint8_t i2c_addr) {
  i2c_addr = i2c_addr;
}

void BombDisplay::initDisplay() {
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21); // turn on oscillator
  Wire.endTransmission();

  blinkRate(0); // default
  setBrightness(15); // default
  delay(100);
  bombDisplayClear();
  writeDisplay();
  delay(100);

}

void BombDisplay::bombDisplayClear() {
  for (uint8_t i = 0; i < 8; i++) {
    displaybuffer[i] = 0;
  }
}


void BombDisplay::writeDisplay() {
  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)0x00); // start at address $00

  for (uint8_t i = 0; i < 8; i++) {
    Wire.write(displaybuffer[i] & 0xFF);
    Wire.write(displaybuffer[i] >> 8);
  }
  Wire.endTransmission();
}

void BombDisplay::setBrightness(uint8_t b) {
  if (b > 15) b = 15;
  Wire.beginTransmission(i2c_addr);
  Wire.write(HT16K33_CMD_BRIGHTNESS | b);
  Wire.endTransmission();
}

void BombDisplay::blinkRate(uint8_t b) {
  Wire.beginTransmission(i2c_addr);
  if (b > 3) b = 0; // turn off if not sure
  Wire.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
  Wire.endTransmission();
}

void BombDisplay::setTime(byte hours, byte minutes) {

}

void BombDisplay::writeBuffer() {
  for (int i = 0; i < 8; i++) {
    if (i == 2) {
      if (apostrophe) {
        displaybuffer[2] = 0b0000000010000;
      } else {
        displaybuffer[2] = displaybuffer[2] & ~0b0000000010000;
      }
    }
    uint16_t token = displaybuffer[i];
    if (i >= 3 && i <= 6) {
      if (commas[i - 3] == 0) {
        token = token & ~0b1000000000000;
      } else {
        token = token | commas[i - 3];
      }
    }
    displaybuffer[i] = token;
  }
}

void BombDisplay::setBombTime(int seconds) {
  // seconds till 'explosion'
  int _seconds = seconds;

  if (_seconds > 9999) {
    _seconds = 9999;
  }
  if (_seconds < 0) {
    _seconds = 0;
  }

  int hh = _seconds / 1000;
  int hl = (_seconds % 1000) / 100;
  int lh = (_seconds % 100) / 10;
  int ll = _seconds % 10;

  displaybuffer[3] = bombclocktable[hh];
  displaybuffer[4] = bombclocktable[hl];
  displaybuffer[5] = bombclocktable[lh];
  displaybuffer[6] = bombclocktable[ll];

  writeBuffer();
  writeDisplay();
}

void BombDisplay::setHours(byte hours) {
  byte h = hours;
  if (h >= 24) {
    h = h % 24;
  }
  byte hh = h / 10;
  byte hl = h % 10;

  displaybuffer[3] = bombclocktable[hh];
  displaybuffer[4] = bombclocktable[hl];

  writeBuffer();
  writeDisplay();
}

void BombDisplay::setMinutes(byte minutes) {
  byte m = minutes;
  if (m >= 60) {
    m = m % 60;
  }
  byte mh = m / 10;
  byte ml = m % 10;

  displaybuffer[5] = bombclocktable[mh];
  displaybuffer[6] = bombclocktable[ml];

  writeBuffer();
  writeDisplay();
}

void BombDisplay::setColon(boolean on) {
  if (on) {
    displaybuffer[1] = displaybuffer[1] | 0b00001000;
  } else {
    displaybuffer[1] = displaybuffer[1] & ~0b00001000;
  }
  writeBuffer();
  writeDisplay();
}

void BombDisplay::setComma(byte comma, boolean on) {
  byte c = comma;
  if (c > 3) {
    c = c % 4;
  } else if (c < 0) {
    c = 3;
  }
  if (on) {
    commas[c] = 0b1000000000000;
  } else {
    commas[c] = 0x0;
  }
  writeBuffer();
  writeDisplay();
}

void BombDisplay::setApostrophe(boolean on) {
  apostrophe = on;
  writeBuffer();
  writeDisplay();
}
