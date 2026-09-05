#pragma once
#include "Screen.h"
#include "StatsDisplay.h"
#include "BackgroundDisplay.h"

class StatsScreen : public Screen {
public:
  StatsScreen(StatsDisplay& stats, BackgroundDisplay& background);

  void enter() override;
  void exit() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;

private:
  StatsDisplay& stats;
  BackgroundDisplay& background;
};
