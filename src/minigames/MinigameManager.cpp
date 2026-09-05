#include "MinigameManager.h"
#include <Arduino.h>
#include "../EconomyManager.h"

extern EconomyManager Economy; // defined in main.cpp

namespace {
  constexpr unsigned long GAME_OVER_DELAY = 3000; // ms to show the game-over screen before returning to idle
  constexpr int MONEY_PER_POINT = 1; // how much each score point is worth
}

MinigameManager::MinigameManager(TFT_eSprite& canvasRef)
  : canvas(canvasRef), flappyBird(canvasRef), activeGame(nullptr), gameOverTime(0) {
}

void MinigameManager::playFlappyBird() {
  activeGame = &flappyBird;
  flappyBird.start();
  gameOverTime = 0;
}

void MinigameManager::update() {
  if (!activeGame) return;

  activeGame->update();

  if (activeGame->isGameOver() && gameOverTime == 0) {
    gameOverTime = millis();
    Economy.earn(activeGame->getScore() * MONEY_PER_POINT);
  }
}

void MinigameManager::draw() {
  if (activeGame) activeGame->draw();
}

void MinigameManager::primaryAction() {
  if (activeGame) activeGame->primaryAction();
}

bool MinigameManager::isGameOver() const {
  return activeGame && activeGame->isGameOver();
}

bool MinigameManager::isReadyToExit() const {
  return gameOverTime != 0 && (millis() - gameOverTime >= GAME_OVER_DELAY);
}
