#pragma once
#include <TFT_eSPI.h>
#include "../TamaState.h"
#include "../EconomyManager.h"
#include "../menu/MenuStack.h"
#include "BackgroundDisplay.h"
#include "AnimationDisplay.h"
#include "StatsDisplay.h"
#include "MenuDisplay.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();

  void updateAnimation();
  void playFeedAnimation();
  void refreshBackground();
  void clearScreen();
  void drawStats(const TamaState& tama, const EconomyManager& economy);
  void checkDisplayMenu(MenuStack& menuStack);
  void invalidateMenu();

  TFT_eSprite& getCanvas();

private:
  TFT_eSPI tft;
  TFT_eSprite canvas;
  BackgroundDisplay background;
  AnimationDisplay animator;
  StatsDisplay stats;
  MenuDisplay menuDisplay;
};
