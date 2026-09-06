#pragma once
#include "Screen.h"
#include "ScreenManager.h"
#include "../display/DisplayManager.h"

class StatsScreen : public Screen {
public:
  StatsScreen(DisplayManager& display, ScreenManager& screens, Screen& idleScreen, Screen& menuScreen);

  void enter() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonB() override;
  void onButtonC() override;

private:
  DisplayManager& display;
  ScreenManager& screens;
  Screen& idleScreen;
  Screen& menuScreen;
};
