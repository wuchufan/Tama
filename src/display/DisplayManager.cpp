#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : background(tft), animator(tft, background), stats(tft), menuDisplay(tft, background, animator, stats) {
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true);
  background.draw();

  animator.begin();
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
