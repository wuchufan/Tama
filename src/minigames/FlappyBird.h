#pragma once
#include <TFT_eSPI.h>
#include "Minigame.h"

class FlappyBird : public Minigame {
public:
  explicit FlappyBird(TFT_eSprite& canvas);

  void start() override; // resets game state

  void update() override;
  void draw() override;
  void primaryAction() override; // flaps

  bool isGameOver() const override;
  int getScore() const override;

private:
  struct Pipe {
    int x;
    int gapY;
    bool scored;
  };

  static const int PIPE_COUNT = 3;

  TFT_eSprite& canvas;

  float birdY;
  float birdVelocity;
  bool gameOver;
  int score;
  Pipe pipes[PIPE_COUNT];

  void resetPipes();
  void updatePipes();
  void drawPipes();
  void drawBird();
  bool checkCollision() const;
};
