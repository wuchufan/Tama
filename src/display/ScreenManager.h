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

  bool isShowing(const Screen& screen) const {
    return current == &screen;
  }

private:
  Screen* current = nullptr;
};
