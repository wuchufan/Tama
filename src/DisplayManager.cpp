#include "DisplayManager.h"
#include "Sprites.h"

const unsigned long DisplayManager::FRAME_DELAY = 150; // same cadence as animation.ino

DisplayManager::DisplayManager()
  : character(&tft), frameIndex(0), lastFrameTime(0),
    wasMenuOpen(false), lastDrawnScreen(nullptr), lastDrawnSelectedIndex(-1) {
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  character.setColorDepth(16);     // RGB565
  character.createSprite(100, 100);
  character.setSwapBytes(true);
}

void DisplayManager::update(const TamaState& tama) {
  if (millis() - lastFrameTime >= FRAME_DELAY) {
    lastFrameTime = millis();
    frameIndex = (frameIndex + 1) % IDLE_FRAME_COUNT;
    drawCharacter();
  }
  drawStats(tama);
}

void DisplayManager::checkMenu(const TamaState& tama, MenuStack& menuStack) {
  if (!menuStack.isOpen()) {
    if (wasMenuOpen) {
      // just closed: wipe the menu screen and force one fresh draw of the home screen
      tft.fillScreen(TFT_BLACK);
      drawCharacter();
      drawStats(tama);
      wasMenuOpen = false;
      lastDrawnScreen = nullptr;
      lastDrawnSelectedIndex = -1;
    }
    return;
  }

  MenuScreen* screen = menuStack.current();
  bool justOpened = !wasMenuOpen;
  bool screenChanged = (screen != lastDrawnScreen);

  // redraw only when it just opened, the screen changed (push/pop), or selection moved
  if (justOpened || screenChanged || screen->getSelectedIndex() != lastDrawnSelectedIndex) {
    drawItemList(*screen);
    lastDrawnScreen = screen;
    lastDrawnSelectedIndex = screen->getSelectedIndex();
  }
  wasMenuOpen = true;
}

void DisplayManager::drawItemList(MenuScreen& screen) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);

  for (int i = 0; i < screen.getItemCount(); i++) {
    tft.setTextColor(i == screen.getSelectedIndex() ? TFT_YELLOW : TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 20 + i * 22);
    tft.printf("%s%s", i == screen.getSelectedIndex() ? "-> " : "   ", screen.getLabel(i));
  }
}

void DisplayManager::drawCharacter() {
  character.pushImage(0, 0, 100, 100, idle_frames[frameIndex]);
  character.pushSprite(50, 20); // placeholder position, tune to your panel
}

void DisplayManager::drawStats(const TamaState& tama) {
  tft.setTextSize(2);

  drawStat(10, 130, "Food", tama.food);
  drawStat(10, 152, "Happy", tama.happiness);
  drawStat(10, 174, "Energy", tama.energy);
  drawStat(10, 196, "Clean", tama.cleanliness);
}

void DisplayManager::drawStat(int x, int y, const char* label, int value) {
  tft.setTextColor(value <= 20 ? TFT_RED : TFT_WHITE, TFT_BLACK);
  tft.setCursor(x, y);
  tft.printf("%s:%d  ", label, value);
}
