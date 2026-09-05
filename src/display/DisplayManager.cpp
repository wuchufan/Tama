#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : canvas(&tft),
    background(tft), animator(tft, background), stats(tft), menuDisplay(tft, background, animator, stats, canvas),
    showingStats(false) {
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true);
  background.draw();

  animator.begin();

  canvas.setColorDepth(16);
  canvas.createSprite(240, 240);
  canvas.setSwapBytes(true);
}

void DisplayManager::update(const TamaState& tama, const EconomyManager& economy) {
  if (showingStats) {
    stats.draw(tama, economy);
    return;
  }

  animator.update();
}

void DisplayManager::checkDisplayMenu(const TamaState& tama, MenuStack& menuStack) {
  if (menuStack.isOpen()) showingStats = false;
  menuDisplay.checkMenu(tama, menuStack);
}

void DisplayManager::playFeedAnimation() {
  animator.playFeedAnimation();
}

TFT_eSprite& DisplayManager::getCanvas() {
  return canvas;
}

void DisplayManager::toggleStatsScreen() {
  showingStats = !showingStats;
  if (showingStats) {
    background.clearScreen(); // black backdrop for the stats screen
  } else {
    background.draw(); // restore the wallpaper before resuming the walking animation
  }
}
