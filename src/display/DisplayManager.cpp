#include "DisplayManager.h"

DisplayManager::DisplayManager()
  : canvas(&tft),
    background(tft), animator(tft, background), stats(tft), menuDisplay(tft, background, animator, stats, canvas),
    idleScreen(animator), statsScreen(stats, background) {
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

  screens.switchTo(idleScreen);
}

void DisplayManager::update(const TamaState& tama, const EconomyManager& economy) {
  screens.update(tama, economy);
}

void DisplayManager::checkDisplayMenu(const TamaState& tama, MenuStack& menuStack) {
  if (menuStack.isOpen() && !screens.isShowing(idleScreen)) screens.switchTo(idleScreen);
  menuDisplay.checkMenu(tama, menuStack);
}

void DisplayManager::playFeedAnimation() {
  animator.playFeedAnimation();
}

TFT_eSprite& DisplayManager::getCanvas() {
  return canvas;
}

void DisplayManager::toggleStatsScreen() {
  if (screens.isShowing(statsScreen)) {
    screens.switchTo(idleScreen);
  } else {
    screens.switchTo(statsScreen);
  }
}
