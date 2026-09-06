#pragma once
#include <TFT_eSPI.h>
#include "MenuWindow.h"

class MenuGrid {
public:
  void draw(MenuWindow& screen, TFT_eSprite& canvas);
};
