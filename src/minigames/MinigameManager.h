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

  bool isReadyToExit() const; // true once the game-over delay has elapsed

private:
  FlappyBird flappyBird;
  Minigame* activeGame;
  unsigned long gameOverTime;
};
