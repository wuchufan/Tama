#include "StatsDisplay.h"

StatsDisplay::StatsDisplay(TFT_eSPI& tftRef) : tft(tftRef) {
}

void StatsDisplay::draw(const TamaState& tama) {
  tft.setTextSize(2);

  drawStat(10, 130, "Food", tama.food);
  drawStat(10, 152, "Happy", tama.happiness);
  drawStat(10, 174, "Energy", tama.energy);
  drawStat(10, 196, "Clean", tama.cleanliness);
}

void StatsDisplay::drawStat(int x, int y, const char* label, int value) {
  tft.setTextColor(value <= 20 ? TFT_RED : TFT_WHITE, TFT_BLACK);
  tft.setCursor(x, y);
  tft.printf("%s:%d  ", label, value);
}
