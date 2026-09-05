#pragma once
#include "Screen.h"

class ScreenManager {
public:
  void switchTo(Screen& next) {
    if (current) current->exit();
    current = &next;
    current->enter();
  }

  void update(const TamaState& tama, const EconomyManager& economy) {
    if (current) current->update(tama, economy);
  }

  void onButtonA() { if (current) current->onButtonA(); }
  void onButtonB() { if (current) current->onButtonB(); }
  void onButtonC() { if (current) current->onButtonC(); }

  bool isShowing(const Screen& screen) const {
    return current == &screen;
  }

private:
  Screen* current = nullptr;
};
