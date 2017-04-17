/*
    Buttons for the Defusable Alarm Clock Example

    J.A. Korten
    April 7, 2017
    V1.0

*/


const int buttonA = 2;
const int buttonB = 3;
const int buttonC = 4;

/*
  functions for buttons

*/

void updateButtonStates() {
  if (checkButtonA()) {
    if (checkButtonB()) {
      if (checkButtonA()) {
        countingDown = false;
        setArmed(false);
      }
    } else {
      countingDown = true;
      setArmed(true);
      updateSpeed = 1000; // resets update speed 
      updateShakerState(500);
    }
  }
}


void setupButtons() {
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
}

boolean checkButtonA() {
  return digitalRead(buttonA);
}

boolean checkButtonB() {
  return digitalRead(buttonB);
}

boolean checkButtonC() {
  return digitalRead(buttonC);
}


