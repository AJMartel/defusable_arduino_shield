/*
    Tilt sensor code for the Defusable Alarm Clock Example

    J.A. Korten
    April 7, 2017
    V1.0

*/

const int shaker = 16;
int initialShakerState = 0;

void setupShaker() {
  pinMode(shaker, INPUT);
  updateShakerState(0);
}

void updateShakerState(int delayMS) {
  shakeDelay = delayMS;
  initialShakerState = checkShaker();
}

boolean checkShaker() {
  return digitalRead(shaker);
}

void updateShaker() {
  Serial.println(checkShaker());
  if (checkShaker() != initialShakerState) {
    // Do something e.g. make count down going faster
    updateSpeed = 100;
  }
}

