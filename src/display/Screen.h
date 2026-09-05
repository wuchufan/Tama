#pragma once
#include "../TamaState.h"
#include "../EconomyManager.h"

class Screen {
public:
  virtual ~Screen() = default;

  virtual void enter() {} // called once when this screen becomes active
  virtual void exit() {}  // called once when leaving this screen
  virtual void update(const TamaState& tama, const EconomyManager& economy) = 0;
};
