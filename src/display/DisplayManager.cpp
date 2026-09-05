#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : canvas(&tft),
    background(tft), animator(tft, background), stats(tft), menuDisplay(tft, background, animator, stats, canvas) {
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

void DisplayManager::update(const TamaState& tama) {
  animator.update();
  if (animator.isIdle()) {
    // stats.draw(tama);
  }
}

void DisplayManager::checkDisplayMenu(const TamaState& tama, MenuStack& menuStack) {
  menuDisplay.checkMenu(tama, menuStack);
}

void DisplayManager::playFeedAnimation() {
  animator.playFeedAnimation();
}

TFT_eSprite& DisplayManager::getCanvas() {
  return canvas;
}
