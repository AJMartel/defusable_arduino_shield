#include "pitches.h"

const int buzzerPin = 9;

void makeBleep() {
  int noteDuration = updateSpeed / 2;
  tone(buzzerPin, NOTE_C4, noteDuration);
}

