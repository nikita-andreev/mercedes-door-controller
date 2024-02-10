#ifndef Door_h
#define Door_h

#include <Arduino.h>

#define DOOR_OPEN_PIN 4
#define DOOR_CLOSE_PIN 5
#define DOOR_SENSOR_PIN 14
#define MAX_CURRENT_VALUE 512
#define MAX_OVERLOAD_TIME 500
#define MIN_OPERATION_SUCCESS_TIME 5000
#define MAX_OPERATION_TIME 10000

enum class DoorState {Error, Opened, Closed, Opening, Closing};

class Door {
  public:
    Door();
    void setup();
    void run();
    void open();
    void close();
    DoorState state();
  private:
    DoorState _state;
    unsigned long overloadStartTime;
    unsigned long operationStartTime;
    void stop();
    int motorCurrent();
    bool isBlocked();
    unsigned long operationTime();
};

#endif