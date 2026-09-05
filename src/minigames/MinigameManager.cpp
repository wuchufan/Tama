#include "MinigameManager.h"
#include <Arduino.h>

namespace {
  constexpr unsigned long GAME_OVER_DELAY = 3000; // ms to show the game-over screen before returning to idle
}

MinigameManager::MinigameManager(TFT_eSprite& canvasRef)
  : canvas(canvasRef), flappyBird(canvasRef), activeGame(nullptr), minigameActive(false), gameOverTime(0) {
}

void MinigameManager::playFlappyBird() {
  activeGame = &flappyBird;
  flappyBird.start();
  minigameActive = true;
  gameOverTime = 0;
}

void MinigameManager::toggleMinigame() {
  minigameActive = !minigameActive;
}

void MinigameManager::update() {
  if (!minigameActive || !activeGame) return;

  activeGame->update();

  if (activeGame->isGameOver()) {
    if (gameOverTime == 0) gameOverTime = millis();

    if (millis() - gameOverTime >= GAME_OVER_DELAY) {
      minigameActive = false;
      gameOverTime = 0;
    }
  }
}

void MinigameManager::draw() {
  if (minigameActive && activeGame) activeGame->draw();
}

void MinigameManager::primaryAction() {
  if (minigameActive && activeGame) activeGame->primaryAction();
}

bool MinigameManager::isGameOver() const {
  return activeGame && activeGame->isGameOver();
}

bool MinigameManager::isMinigameActive() const {
  return minigameActive;
}
