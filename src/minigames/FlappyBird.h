#pragma once
#include <TFT_eSPI.h>

class FlappyBird {
public:
  explicit FlappyBird(TFT_eSprite& canvas);

  void start(); // resets game state

  void update();
  void draw();
  void flap();

  bool isGameOver() const;
  int getScore() const;

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
