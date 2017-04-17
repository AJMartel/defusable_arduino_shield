/*
    Leds for the Defusable Alarm Clock Example

    J.A. Korten
    April 7, 2017
    V1.0

*/


const int GREEN_LED = 13;
const int RED_LED = 17;


void setupLeds() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void setArmed(boolean armed) {
  digitalWrite(GREEN_LED, !armed);
  digitalWrite(RED_LED, armed);
}

void updateRedLed() {
  // blink if counter < 50?
}

