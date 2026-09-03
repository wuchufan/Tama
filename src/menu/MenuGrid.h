#pragma once
#include <TFT_eSPI.h>
#include "MenuScreen.h"

class MenuGrid {
public:
  explicit MenuGrid(TFT_eSPI& tft);

  void draw(MenuScreen& screen);

private:
  TFT_eSPI& tft;
};
