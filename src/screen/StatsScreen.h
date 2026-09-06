#pragma once
#include "Screen.h"
#include "ScreenManager.h"
#include "../display/StatsDisplay.h"
#include "../display/BackgroundDisplay.h"

class StatsScreen : public Screen {
public:
  StatsScreen(StatsDisplay& stats, BackgroundDisplay& background, ScreenManager& screens, Screen& idleScreen, Screen& menuScreen);

  void enter() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonB() override;
  void onButtonC() override;

private:
  StatsDisplay& stats;
  BackgroundDisplay& background;
  ScreenManager& screens;
  Screen& idleScreen;
  Screen& menuScreen;
};
