#include "door.h"

Door::Door() {
  _state = DoorState::Error;
  overloadStartTime = 0;
  operationStartTime = 0;
}

bool Door::isBlocked()
{
  unsigned long overloadTime = 0;
  if(motorCurrent() > MAX_CURRENT_VALUE)
  {
    if(overloadStartTime == 0) {
      overloadStartTime = millis(); 
    }
    overloadTime = millis() - overloadStartTime;
  } 
  else
  {
    overloadStartTime = 0;
  }
  return overloadTime > MAX_OVERLOAD_TIME;
}

void Door::run()
{
  if (_state == DoorState::Error) {
    open();
  }
  
  if (isBlocked() == true) {
    stop();
    if(operationTime() > 0 && operationTime() < MIN_OPERATION_SUCCESS_TIME) {
      _state = DoorState::Error;
    } else {
      switch(_state)
      {
        case DoorState::Closing:
          _state = DoorState::Closed;
          break;
        case DoorState::Opening:
          _state = DoorState::Opened;
          break;
        default:
          _state = DoorState::Error;   
      };
    }
  }
}

void Door::setup()
{
  pinMode(DOOR_OPEN_PIN, OUTPUT);
  pinMode(DOOR_CLOSE_PIN, OUTPUT);
  stop();
  pinMode(DOOR_SENSOR_PIN, INPUT);
}

void Door::stop()
{
  digitalWrite(DOOR_OPEN_PIN, HIGH);
  digitalWrite(DOOR_CLOSE_PIN, HIGH);
}

void Door::open()
{ 
  if(_state != DoorState::Opening) {
    stop();
    digitalWrite(DOOR_OPEN_PIN, LOW);
    _state = DoorState::Opening;
  }
}

void Door::close()
{
  if(_state != DoorState::Closing) {
    stop();
    digitalWrite(DOOR_CLOSE_PIN, LOW);
    operationStartTime = millis();
    _state = DoorState::Closing;
  } 
}

int Door::motorCurrent()
{
  return analogRead(DOOR_SENSOR_PIN);
}

unsigned long Door::operationTime()
{
  if(operationStartTime == 0) {
    return 0;
  } else {
    return millis() - operationStartTime;
  }
}
