/*
    Display stuff for the Defusable Alarm Clock Example

    J.A. Korten
    April 17, 2017
    V1.0

*/

void setupDisplay() {
  Wire.begin();
  bombDisplay.initDisplay();
}

void updateDisplay() {
  updateCountDown();
}

