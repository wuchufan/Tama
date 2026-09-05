#pragma once
#include <TFT_eSPI.h>
#include "../TamaState.h"
#include "../menu/MenuStack.h"
#include "../EconomyManager.h"
#include "BackgroundDisplay.h"
#include "AnimationDisplay.h"
#include "StatsDisplay.h"
#include "MenuDisplay.h"
#include "ScreenManager.h"
#include "IdleScreen.h"
#include "StatsScreen.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void update(const TamaState& tama, const EconomyManager& economy);
  void checkDisplayMenu(const TamaState& tama, MenuStack& menuStack);
  void playFeedAnimation();
  void toggleStatsScreen();
  void refreshBackground(); // unconditionally repaints the wallpaper
  TFT_eSprite& getCanvas();

private:
  TFT_eSPI tft;
  TFT_eSprite canvas;
  BackgroundDisplay background;
  AnimationDisplay animator;
  StatsDisplay stats;
  MenuDisplay menuDisplay;
  ScreenManager screens;
  IdleScreen idleScreen;
  StatsScreen statsScreen;
};
