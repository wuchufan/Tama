#include "BackgroundDisplay.h"
#include "../Sprites.h"

const int BackgroundDisplay::SCREEN_WIDTH = 240;
const int BackgroundDisplay::SCREEN_HEIGHT = 240;

BackgroundDisplay::BackgroundDisplay(TFT_eSPI& tftRef) : tft(tftRef) {
}

void BackgroundDisplay::draw() {
  tft.pushImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, main_background);
}

void BackgroundDisplay::drawPatchInto(TFT_eSprite& target, int screenX, int screenY, int width, int height) {
  for (int row = 0; row < height; row++) {
    target.pushImage(0, row, width, 1, &main_background[(screenY + row) * SCREEN_WIDTH + screenX]);
  }
}
