#include "button.h"

static int Button::pressedLevel() {
  return HIGH;
}

Button::Button(byte p) 
{
  init(p, PRESSED_DETECT_DELAY, LONG_PRESSED_DETECT_DELAY, READ_TIMEOUT);
}

Button::Button(byte p, int short_time, int long_time, int fuse_timeout)
{
  init(p, short_time, long_time, fuse_timeout);
}

void Button::init(byte p, int short_time, int long_time, int fuse_timeout)
{
  pin = p;
  short_pressed_min_time = short_time;
  long_pressed_min_time = long_time;
  delay_to_next_read = fuse_timeout;

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
    
    if(pressedTime >= (unsigned long)short_pressed_min_time) 
      pressedEvent = true;
    if(pressedTime >= (unsigned long)long_pressed_min_time)
      {
        pressedEvent = false;
        longPressedEvent = !blockLongPressedEvent;
      }
  }
}

void Button::detectState()
{
  if(millis() - readTimeout > (unsigned long)delay_to_next_read) 
  {
    if(digitalRead(pin) == pressedLevel()) {
      if(state == ButtonState::Released) {
        Serial.println("Pressed " + String(pin));
        timeout = millis();
        state = ButtonState::Pressed;
      }
    } else {
      if(state == ButtonState::Pressed) {
        Serial.println("Released " + String(pin));
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




