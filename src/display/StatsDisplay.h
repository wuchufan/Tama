#pragma once
#include <TFT_eSPI.h>
#include "../TamaState.h"

class StatsDisplay {
public:
  explicit StatsDisplay(TFT_eSPI& tft);

  void draw(const TamaState& tama);

private:
  TFT_eSPI& tft;

  void drawStat(int x, int y, const char* label, int value);
};
