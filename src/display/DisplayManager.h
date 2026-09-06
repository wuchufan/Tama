#pragma once
#include <TFT_eSPI.h>
#include "BackgroundDisplay.h"
#include "AnimationDisplay.h"
#include "StatsDisplay.h"
#include "MenuDisplay.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void playFeedAnimation();
  TFT_eSprite& getCanvas();

  AnimationDisplay& getAnimator();
  BackgroundDisplay& getBackground();
  StatsDisplay& getStats();
  MenuDisplay& getMenuDisplay();

private:
  TFT_eSPI tft;
  TFT_eSprite canvas;
  BackgroundDisplay background;
  AnimationDisplay animator;
  StatsDisplay stats;
  MenuDisplay menuDisplay;
};
