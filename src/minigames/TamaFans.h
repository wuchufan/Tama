#pragma once
#include <TFT_eSPI.h>
#include "Minigame.h"

class TamaFans : public Minigame {
public:
  explicit TamaFans(TFT_eSprite& canvas);

  void start() override;
  void update() override;
  void draw() override;
  void actionB() override;   // answer the fan on the right
  void actionA() override; // answer the fan on the left

  bool isGameOver() const override;
  int getScore() const override;

private:
  enum class Wish { AUTOGRAPH, MAIL, BUG };

  TFT_eSprite& canvas;

  bool fanOnLeft;
  Wish wish;
  unsigned long fanArrivedTime;
  unsigned long fanDuration;
  bool gameOver;
  int score;

  void nextFan();
  void answer(bool leftSide);
  void drawFan(int x);
};
