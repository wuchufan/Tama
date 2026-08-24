#include "BackgroundDisplay.h"
#include "../Sprites.h"

const int BackgroundDisplay::SCREEN_WIDTH = 240;
const int BackgroundDisplay::SCREEN_HEIGHT = 240;

BackgroundDisplay::BackgroundDisplay(TFT_eSPI& tftRef) : tft(tftRef) {
}

void BackgroundDisplay::draw() {
  tft.pushImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, main_background);
}

// Copies the rectangle of main_background behind screen position (screenX, screenY),
// sized width x height, into target's own buffer starting at local (0, 0). Done row by
// row because each source row is SCREEN_WIDTH pixels wide while the patch is narrower,
// so a single contiguous copy would grab the wrong pixels partway through each row.
void BackgroundDisplay::drawPatchInto(TFT_eSprite& target, int screenX, int screenY, int width, int height) {
  for (int row = 0; row < height; row++) {
    target.pushImage(0, row, width, 1, &main_background[(screenY + row) * SCREEN_WIDTH + screenX]);
  }
}
