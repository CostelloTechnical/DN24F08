#include "dn24f08.h"

const float gains[dn24f08::_analogPins] PROGMEM = { 
    1.0, 1.0, 1.0, 1.0,  // Current input gains: I1, I2, I3, I4.
    1.0, 1.0, 1.0, 1.0   // Voltage input gains: V1, V2, V3, V4.
};

const float offsets[dn24f08::_analogPins] PROGMEM = { 
    0.0, 0.0, 0.0, 0.0,  // Current input offsets: I1, I2, I3, I4.
    0.0, 0.0, 0.0, 0.0   // Voltage input offsets: V1, V2, V3, V4.
};

dn24f08 plc (gains, offsets);

uint32_t printTimeCache_ms = 0;

void setup() {
  plc.init(115200);

  /* 
    Optional - Only for use with the engineAnalogAverage() function. 
    This set if the averaging should be time based or number of readings based, followed by the time/readings.
    Allowable types: TIME_MS, READINGS.
  */
  plc.setAnalogEngineType(TIME_MS, 100);

  plc.getAnalog(V1);  // Read voltage input 1. (Volts)
  plc.getAnalog(I1);  // Read current input 1. (mAmps)
}

void loop() {
  /* 
    Optional - The engineAnalogAverage() is a non-blocking function that iterates through the analog inputs.
    Below I've put together an example where the most recent analog average is printed to the serial monitor every second.
  */
  plc.engineAnalogAverage();
  if (millis() - printTimeCache_ms > 1000) {
    plc.print(F("I1 = "));
    plc.println(plc.getAnalogAverage(I1));
    plc.write('\r');
    plc.print(F("V1 = "));
    plc.println(plc.getAnalogAverage(V1));
    plc.write('\r');
    printTimeCache_ms = millis();
  }
}