#pragma once
#include <TFT_eSPI.h>
#include "MenuScreen.h"

class MenuList {
public:
  explicit MenuList(TFT_eSPI& tft);

  void draw(MenuScreen& screen);

private:
  TFT_eSPI& tft;
};
