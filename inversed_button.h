#ifndef InversedButton_h
#define InversedButton_h
#include "button.h"

class InversedButton : public Button {
  int pressedLevel();
  using Button::Button;
};
#endif