#ifndef Button_h
#define Button_h
#include <Arduino.h>

#define PRESSED_DETECT_DELAY 400
#define LONG_PRESSED_DETECT_DELAY 1800
#define READ_TIMEOUT 500

enum class ButtonState {Pressed, Released};

class Button {
  public:
    static int pressedLevel();
    Button(byte pin);
    void setup();
    void run();
    bool isPressed();
    bool isLongPressed();
  private:
    void detectState();
    byte pin;
    ButtonState state;
    bool pressedEvent;
    bool longPressedEvent;
    bool blockLongPressedEvent;
    unsigned long timeout;
    unsigned long readTimeout;
};
#endif