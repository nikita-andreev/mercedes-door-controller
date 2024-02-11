#include "door.h"

Door::Door() {
  _state = DoorState::Error;
  overloadStartTime = 0;
  operationStartTime = 0;
}

bool Door::isBlocked()
{
  unsigned long overloadTime = 0;
  if(motorCurrent() < MAX_CURRENT_VALUE) // The op < is right, since 512 = 0A, 310 = 5A
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
    Serial.println("Opening the door due to error");
    open();
  }

  if(operationTime() > MAX_OPERATION_TIME)
  {
    Serial.println("Door operation timeout error");
    stop();
    if(_state == DoorState::Opening) {
      Serial.println("Assume the door is opened");
      _state = DoorState::Opened;
      operationStartTime = 0;
    } else {
      Serial.println("Error. let's try to open the door");
      _state = DoorState::Error;
    }
  }
  
  if (isBlocked() == true) {
    Serial.println("Door is blocked");
    stop();
    if(_state == DoorState::Closing && operationTime() > 0 && operationTime() < MIN_OPERATION_SUCCESS_TIME) {
      Serial.println("Something wrong. Error");
      _state = DoorState::Error;
    } else {
      switch(_state)
      {
        case DoorState::Closing:
          Serial.println("The door is closed"); 
          _state = DoorState::Closed;
          operationStartTime = 0;
          break;
        case DoorState::Opening:
          Serial.println("The door is opened"); 
          _state = DoorState::Opened;
          operationStartTime = 0;
          break;
        default:
          Serial.println("Door state error detected!");
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
    Serial.println("The door is opening");
    stop();
    digitalWrite(DOOR_OPEN_PIN, LOW);
    operationStartTime = millis();
    _state = DoorState::Opening;
  }
}

void Door::close()
{
  if(_state != DoorState::Closing) {
    Serial.println("The door is closing");
    stop();
    digitalWrite(DOOR_CLOSE_PIN, LOW);
    operationStartTime = millis();
    _state = DoorState::Closing;
  } 
}

int Door::motorCurrent()
{
  #ifndef MOCK_CURRENT_SENSOR
  return analogRead(DOOR_SENSOR_PIN);
  #else
  if(operationTime() > MIN_OPERATION_SUCCESS_TIME) 
    return 200;
  else 
    return 509;
  #endif   
}

unsigned long Door::operationTime()
{
  if(operationStartTime == 0) {
    return 0;
  } else {
    return millis() - operationStartTime;
  }
}

DoorState Door::state() {
  return _state;
}
