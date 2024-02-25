#define DEBUG 1

#include <Arduino.h>
#include "door.h"
#include "button.h"
#include "inversed_button.h"

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
Button lightsRemoteButton(3, 100, 2000, 800);
InversedButton doorInnerButton(6, 100, 800, 1500);
InversedButton lightsInnerButton(7, 100, 10000, 1500);
bool lightsState;


void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  door.setup();
  doorRemoteButton.setup();
  doorInnerButton.setup();
  lightsRemoteButton.setup();
  lightsInnerButton.setup();

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  lightsState = false;

  delay(3000);
}

void loop() {
  door.run();
  doorRemoteButton.run();
  doorInnerButton.run();
  lightsRemoteButton.run();
  lightsInnerButton.run();

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

  if(doorInnerButton.isLongPressed()) {
    Serial.println("Inner door button is long pressed");
    switch(door.state()) {
      case DoorState::Closed:
        door.open();
        break;
      case DoorState::Opened:
        door.close();
        break;
      default:
        Serial.println("The door control button pressed while the door is busy (Inner button)");    
    };
  }

  if(lightsRemoteButton.isLongPressed() | lightsInnerButton.isPressed())
  {
    Serial.println("Lights button has long pressed...");    
    digitalWrite(10, lightsState == true ? HIGH : LOW);
    lightsState = !lightsState;
  }
    

  if(door.hasOpened()) {
    Serial.println("The door was opened successfully. Turning lights on?");
  }

  if(door.hasClosed()) {
    Serial.println("The door was closed successfully. Turning lights off?");
    lightsState = false;
    digitalWrite(10, HIGH);
  } 
}


