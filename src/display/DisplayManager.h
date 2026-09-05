#pragma once
#include <TFT_eSPI.h>
#include "../TamaState.h"
#include "../menu/MenuStack.h"
#include "../EconomyManager.h"
#include "BackgroundDisplay.h"
#include "AnimationDisplay.h"
#include "StatsDisplay.h"
#include "MenuDisplay.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void update(const TamaState& tama, const EconomyManager& economy);
  void checkDisplayMenu(const TamaState& tama, MenuStack& menuStack);
  void playFeedAnimation();
  TFT_eSprite& getCanvas();

private:
  TFT_eSPI tft;
  TFT_eSprite canvas;
  BackgroundDisplay background;
  AnimationDisplay animator;
  StatsDisplay stats;
  MenuDisplay menuDisplay;
};
