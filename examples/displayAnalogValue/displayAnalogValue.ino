#include "dn24f08.h"

dn24f08 plc;

void setup() {
  plc.init();

  plc.setDisplayEngineType(ANALOG);
  plc.setDisplayAnalogPin(V1);
  plc.setAnalogEngineType(TIME_MS, 100);
}

void loop() {

  plc.engineAnalogAverage();
  plc.engineDisplay();
}