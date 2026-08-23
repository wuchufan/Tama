#pragma once
#include <TFT_eSPI.h>
#include "../TamaState.h"
#include "../menu/MenuStack.h"
#include "AnimationDisplay.h"
#include "StatsDisplay.h"
#include "MenuDisplay.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void update(const TamaState& tama);
  void checkMenu(const TamaState& tama, MenuStack& menuStack);
  void playFeedAnimation();

private:
  TFT_eSPI tft;
  AnimationDisplay animator;
  StatsDisplay stats;
  MenuDisplay menuDisplay;
};
