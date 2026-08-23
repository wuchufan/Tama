#pragma once
#include <TFT_eSPI.h>
#include "TamaState.h"
#include "menu/MenuStack.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void update(const TamaState& tama);
  void checkMenu(const TamaState& tama, MenuStack& menuStack);
  void playAnimation(const uint16_t* const frames[], int frameCount, unsigned long frameDelay, int repeatCount = 1);

private:
  TFT_eSPI tft;
  TFT_eSprite character;
  static const unsigned long FRAME_DELAY;

  const uint16_t* const* activeFrames;
  int activeFrameCount;
  unsigned long activeFrameDelay;
  bool activeLoops;
  int animRepeatsRemaining;

  int frameIndex;
  unsigned long lastFrameTime;

  bool wasMenuOpen;
  MenuScreen* lastDrawnScreen;
  int lastDrawnSelectedIndex;

  void drawCharacter();
  void drawStats(const TamaState& tama);
  void drawStat(int x, int y, const char* label, int value);
  void drawItemList(MenuScreen& screen);
  void returnToIdle();
};
