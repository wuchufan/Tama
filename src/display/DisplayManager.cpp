#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : animator(tft), stats(tft), menuDisplay(tft, animator, stats) {
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  animator.begin();
}

void DisplayManager::update(const TamaState& tama) {
  animator.update();
  if (animator.isIdle()) {
    stats.draw(tama);
  }
}

void DisplayManager::checkMenu(const TamaState& tama, MenuStack& menuStack) {
  menuDisplay.checkMenu(tama, menuStack);
}

void DisplayManager::playFeedAnimation() {
  animator.playFeedAnimation();
}
