#pragma once
#include "display/Screen.h"
#include "display/DisplayManager.h"

class NormalDisplayScreen : public Screen {
public:
  explicit NormalDisplayScreen(DisplayManager& display);

  void enter() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonA() override;
  void onButtonB() override;
  void onButtonC() override;

private:
  DisplayManager& display;
};
