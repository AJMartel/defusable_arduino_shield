/*
    Buzzer stuff for the Defusable Alarm Clock Example

    J.A. Korten
    April 17, 2017
    V1.0

*/

#include "pitches.h"

const int buzzerPin = 9;

void makeBleep() {
  int noteDuration = updateSpeed / 2;
  tone(buzzerPin, NOTE_C4, noteDuration);
}

