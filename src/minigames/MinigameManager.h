#pragma once
#include <TFT_eSPI.h>
#include "Minigame.h"
#include "FlappyBird.h"
#include "TamaFans.h"

class MinigameManager {
public:
  explicit MinigameManager(TFT_eSprite& canvas);

  void update();
  void draw();
  void actionB();
  void actionA();

  void playFlappyBird();
  void playTamaFans();

  bool isReadyToExit() const; // true once the game-over delay has elapsed

private:
  FlappyBird flappyBird;
  TamaFans tamaFans;
  Minigame* activeGame;
  unsigned long gameOverTime;
};
