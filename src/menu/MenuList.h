#pragma once
#include <TFT_eSPI.h>
#include "MenuWindow.h"

class MenuList {
public:
  void draw(MenuWindow& screen, TFT_eSprite& canvas);
};
