#pragma once
#include <TFT_eSPI.h>
#include "Minigame.h"
#include "FlappyBird.h"

class MinigameManager {
public:
  explicit MinigameManager(TFT_eSprite& canvas);

  void update();
  void draw();
  void primaryAction();

  void playFlappyBird();
  void toggleMinigame(); // called by the exit button while a game is active

  bool isGameOver() const;
  bool isMinigameActive() const;

private:
  TFT_eSprite& canvas;
  FlappyBird flappyBird;
  Minigame* activeGame;
  bool minigameActive;
  unsigned long gameOverTime;
};
