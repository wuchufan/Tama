#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : canvas(&tft),
    background(tft), animator(tft, background), stats(tft), menuDisplay(canvas) {
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true);

  animator.begin();

  canvas.setColorDepth(16);
  canvas.createSprite(240, 240);
  canvas.setSwapBytes(true);
}

void DisplayManager::updateAnimation() {
  animator.update();
}

void DisplayManager::playFeedAnimation() {
  animator.playFeedAnimation();
}

void DisplayManager::refreshBackground() {
  background.draw();
}

void DisplayManager::clearScreen() {
  background.clearScreen();
}

void DisplayManager::drawStats(const TamaState& tama, const EconomyManager& economy) {
  stats.draw(tama, economy);
}

void DisplayManager::checkDisplayMenu(MenuStack& menuStack) {
  menuDisplay.checkMenu(menuStack);
}

void DisplayManager::invalidateMenu() {
  menuDisplay.invalidate();
}

TFT_eSprite& DisplayManager::getCanvas() {
  return canvas;
}
