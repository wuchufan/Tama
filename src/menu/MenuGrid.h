#pragma once
#include <TFT_eSPI.h>
#include "MenuScreen.h"

class MenuGrid {
public:
  void draw(MenuScreen& screen, TFT_eSprite& canvas);
};
