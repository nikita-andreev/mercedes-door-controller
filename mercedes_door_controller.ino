#define DEBUG 1

#include <Arduino.h>
#include "door.h"
#include "button.h"

/*
pin7 - reserved for buttons
pin6 - reserved for buttons

pin5 - C 
pin4 - A
pin3 - D
pin2 - B

pin8 - relay with current sensor
pin9 - relay with current sensor

pin10 - relay without current sensor
pin11 - relay without current sensor

A0 - current sensor input
*/

Door door;
Button doorRemoteButton(4, 100, 800, 800);


void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  door.setup();
  doorRemoteButton.setup();

  delay(3000);
}

void loop() {
  door.run();
  doorRemoteButton.run();

  if(doorRemoteButton.isLongPressed()) {
    switch(door.state()) {
      case DoorState::Closed:
        door.open();
        break;
      case DoorState::Opened:
        door.close();
        break;
      default:
        Serial.println("The door control button pressed while the door is busy");    
    };
  }  
}


