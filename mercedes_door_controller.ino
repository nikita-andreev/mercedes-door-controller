#include <Arduino.h>
#include "door.h"
#include "button.h"

//Door door;
Button button(5);

  unsigned int a = 65535;
  unsigned int b = 1;


void setup() {
  Serial.begin(9600);
  button.setup();
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);


  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  //door.setup();
}

void loop() {
  button.run();
  
  if(button.isLongPressed()) {
    Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAA");
    digitalWrite(8, !digitalRead(8));
  }
  
  if(button.isPressed()) {
    Serial.println("BBBBBBBBBBBBBBBBBBBBBBBBBBBB");
    digitalWrite(9, !digitalRead(9));
  }
  //Serial.println(analogRead(A0));

  //door.run();
}
