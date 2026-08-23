#pragma once
#include <TFT_eSPI.h>
#include "TamaState.h"
#include "MenuStack.h"

class DisplayManager {
public:
  DisplayManager();

  void begin();
  void update(const TamaState& tama);
  void checkMenu(const TamaState& tama, MenuStack& menuStack);

private:
  TFT_eSPI tft;
  TFT_eSprite character;
  int frameIndex;
  unsigned long lastFrameTime;
  static const unsigned long FRAME_DELAY;

  bool wasMenuOpen;
  MenuScreen* lastDrawnScreen;
  int lastDrawnSelectedIndex;

  void drawCharacter();
  void drawStats(const TamaState& tama);
  void drawStat(int x, int y, const char* label, int value);
  void drawItemList(MenuScreen& screen);
};
