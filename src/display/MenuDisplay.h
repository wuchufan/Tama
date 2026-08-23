#pragma once
#include <TFT_eSPI.h>
#include "../TamaState.h"
#include "AnimationDisplay.h"
#include "StatsDisplay.h"
#include "../menu/MenuStack.h"

class MenuDisplay {
public:
  MenuDisplay(TFT_eSPI& tft, AnimationDisplay& animator, StatsDisplay& stats);

  void checkMenu(const TamaState& tama, MenuStack& menuStack);

private:
  TFT_eSPI& tft;
  AnimationDisplay& animator;
  StatsDisplay& stats;

  bool wasMenuOpen;
  MenuScreen* lastDrawnScreen;
  int lastDrawnSelectedIndex;

  void drawItemList(MenuScreen& screen);
};
