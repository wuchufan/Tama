#pragma once
#include <TFT_eSPI.h>
#include "MenuScreen.h"

class MenuList {
public:
  void draw(MenuScreen& screen, TFT_eSprite& canvas);
};
