#pragma once
#include <TFT_eSPI.h>

class BackgroundDisplay {
public:
  explicit BackgroundDisplay(TFT_eSPI& tft);

  void draw(); // pushes the full background image to the real screen
  void clearScreen();
  // copies the background patch behind the given screen rectangle into target's local (0,0)
  void drawPatchInto(TFT_eSprite& target, int screenX, int screenY, int width, int height);

private:
  TFT_eSPI& tft;
  static const int SCREEN_WIDTH;
  static const int SCREEN_HEIGHT;
};
