#pragma once
#include "Screen.h"
#include "ScreenManager.h"
#include "../display/DisplayManager.h"

class IdleScreen : public Screen {
public:
  IdleScreen(DisplayManager& display, ScreenManager& screens);

  void setStatsScreen(Screen& screen);
  void setMenuScreen(Screen& screen);

  void enter() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonB() override;
  void onButtonC() override;

private:
  DisplayManager& display;
  ScreenManager& screens;
  Screen* statsScreen = nullptr;
  Screen* menuScreen = nullptr;
};
