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

void DisplayManager::playFeedAnimation() {
  animator.playFeedAnimation();
}

TFT_eSprite& DisplayManager::getCanvas() {
  return canvas;
}

AnimationDisplay& DisplayManager::getAnimator() { return animator; }
BackgroundDisplay& DisplayManager::getBackground() { return background; }
StatsDisplay& DisplayManager::getStats() { return stats; }
MenuDisplay& DisplayManager::getMenuDisplay() { return menuDisplay; }
