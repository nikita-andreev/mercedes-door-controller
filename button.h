#ifndef Button_h
#define Button_h
#include <Arduino.h>

#define PRESSED_DETECT_DELAY 400
#define LONG_PRESSED_DETECT_DELAY 1800
#define READ_TIMEOUT 800

enum class ButtonState {Pressed, Released};

class Button {
  public:
    virtual int pressedLevel();
    Button(byte pin);
    Button(byte pin, int short_time, int long_time, int fuse_timeout);
    void setup();
    void run();
    bool isPressed();
    bool isLongPressed();
  private:
    void detectState();
    void init(byte pin, int short_time, int long_time, int fuse_timeout);
    byte pin;
    ButtonState state;
    bool pressedEvent;
    bool longPressedEvent;
    bool blockLongPressedEvent;
    unsigned long timeout;
    unsigned long readTimeout;

    int short_pressed_min_time;
    int long_pressed_min_time;
    int delay_to_next_read; 
};
#endif