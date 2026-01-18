#include "dn24f08.h"

dn24f08 plc;

void setup() {
  plc.init();
}

void loop() {
    plc.engineButtons();
    if(plc.getKeyPressed(KEY1)==true){
        plc.println(F("Key1 Pressed"));
    }
    if(plc.getKeyPressed(KEY2)==true){
        plc.println(F("Key2 Pressed"));
    }
    if(plc.getKeyPressed(KEY3)==true){
        plc.println(F("Key3 Pressed"));
    }
    if(plc.getKeyPressed(KEY4)==true){
        plc.println(F("Key4 Pressed"));
    }
}