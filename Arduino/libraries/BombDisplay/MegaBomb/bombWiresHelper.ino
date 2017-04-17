/*
    'Bomb' wires for the Defusable Alarm Clock Example

    J.A. Korten
    April 7, 2017
    V1.0

*/

const int wireA = 5;
const int wireB = 6;
const int wireC = 7;
const int wireD = 8;
const int wireE = 14;
const int wireF = 15;

/* below you can change behavior for the bomb wires*/

void checkWires() {
  // e.g. if wire F was removed make counter go twice as slow

  // e.g. if wire B was removed subtract 500 from counter

  // e.g. if wire C was removed and B and F are also removed stop counter

  // e.g. if wire D was removed instant detonation

  // e.g. if wire A was removed and C is also removed disarm bomb
  
}



/* below are all the helper functions for the bomb wires*/

void setupBombWires() {
  pinMode(wireA, INPUT);
  pinMode(wireB, INPUT);
  pinMode(wireC, INPUT);
  pinMode(wireD, INPUT);
  pinMode(wireE, INPUT);
  pinMode(wireF, INPUT);
}

boolean checkWireA() {
  return digitalRead(wireA);
}

boolean checkWireB() {
  return digitalRead(wireB);
}

boolean checkWireC() {
  return digitalRead(wireC);
}

boolean checkWireD() {
  return !digitalRead(wireD);
}

boolean checkWireE() {
  return !digitalRead(wireE);
}

boolean checkWireF() {
  return !digitalRead(wireF);
}
