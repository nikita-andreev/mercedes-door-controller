#include "button.h"

static int Button::pressedLevel() {
  return HIGH;
}

Button::Button(byte p) 
{
  pin = p;
  state = ButtonState::Released;
  timeout = millis();
  readTimeout = timeout;
  pressedEvent = false;
  longPressedEvent = false;
  blockLongPressedEvent = false;
}

void Button::setup()
{
  pinMode(pin, INPUT_PULLUP);
}

void Button::run()
{
  detectState();
  if (state == ButtonState::Pressed) 
  {
    unsigned long pressedTime = millis() - timeout;
    pressedEvent = false;
    longPressedEvent = false;
    
    if(pressedTime >= PRESSED_DETECT_DELAY) 
      pressedEvent = true;
    if(pressedTime >= LONG_PRESSED_DETECT_DELAY)
      {
        pressedEvent = false;
        longPressedEvent = !blockLongPressedEvent;
      }
  }
}

void Button::detectState()
{
  if(millis() - readTimeout > READ_TIMEOUT) 
  {
    if(digitalRead(pin) == pressedLevel()) {
      if(state == ButtonState::Released) {
        timeout = millis();
        Serial.println("Will return pressed");
        state = ButtonState::Pressed;
      }
    } else {
      if(state == ButtonState::Pressed) {
        Serial.println("Will return released");
        blockLongPressedEvent = false;
        state = ButtonState::Released;
      }
    }
  }
}

bool Button::isPressed()
{
  if(state == ButtonState::Pressed)
    return false;
  else {
    bool result = pressedEvent;
    if(result) {
      pressedEvent = false;
    }
    return result;
  }    
}

bool Button::isLongPressed()
{
  bool result = longPressedEvent;
  if(result) {
    longPressedEvent = false;
    blockLongPressedEvent = true;
    readTimeout = millis();
  }
  return result;  
}




