#pragma once
#include <TFT_eSPI.h>
#include "../menu/MenuGrid.h"
#include "../menu/MenuList.h"
#include "../menu/MenuStack.h"

class MenuDisplay {
public:
  explicit MenuDisplay(TFT_eSprite& canvas);

  void checkMenu(MenuStack& menuStack);
  void invalidate(); // forces a redraw on the next checkMenu()

private:
  MenuGrid grid;
  MenuList list;
  TFT_eSprite& canvas;

  MenuWindow* lastDrawnScreen;
  int lastDrawnSelectedIndex;
};
