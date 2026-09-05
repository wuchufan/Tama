#include "FlappyBird.h"
#include <Arduino.h>

namespace {
  constexpr int BIRD_X = 60;
  constexpr int BIRD_SIZE = 12;
  constexpr float GRAVITY = 0.35f;
  constexpr float FLAP_STRENGTH = -5.0f;

  constexpr int PIPE_WIDTH = 30;
  constexpr int PIPE_GAP = 70;
  constexpr int PIPE_SPACING = 100;
  constexpr int PIPE_SPEED = 2;
  constexpr int PIPE_MARGIN = 30; // min distance from top/bottom to the gap
}

FlappyBird::FlappyBird(TFT_eSprite& canvasRef)
  : canvas(canvasRef), birdY(120), birdVelocity(0), gameOver(false), score(0) {
}

void FlappyBird::start() {
  birdY = 120;
  birdVelocity = 0;
  gameOver = false;
  score = 0;
  resetPipes();
}

void FlappyBird::primaryAction() {
  if (!gameOver) birdVelocity = FLAP_STRENGTH;
}

void FlappyBird::update() {
  if (gameOver) return;

  birdVelocity += GRAVITY;
  birdY += birdVelocity;

  if (birdY < 0 || birdY + BIRD_SIZE > 240) {
    gameOver = true;
    return;
  }

  updatePipes();
  if (checkCollision()) gameOver = true;
}

void FlappyBird::resetPipes() {
  for (int i = 0; i < PIPE_COUNT; i++) {
    pipes[i].x = 240 + i * PIPE_SPACING;
    pipes[i].gapY = random(PIPE_MARGIN, 240 - PIPE_MARGIN - PIPE_GAP);
    pipes[i].scored = false;
  }
}

void FlappyBird::updatePipes() {
  for (int i = 0; i < PIPE_COUNT; i++) {
    pipes[i].x -= PIPE_SPEED;

    if (!pipes[i].scored && pipes[i].x + PIPE_WIDTH < BIRD_X) {
      pipes[i].scored = true;
      score++;
    }

    if (pipes[i].x + PIPE_WIDTH < 0) {
      int maxX = pipes[0].x;
      for (int j = 1; j < PIPE_COUNT; j++) {
        if (pipes[j].x > maxX) maxX = pipes[j].x;
      }
      pipes[i].x = maxX + PIPE_SPACING;
      pipes[i].gapY = random(PIPE_MARGIN, 240 - PIPE_MARGIN - PIPE_GAP);
      pipes[i].scored = false;
    }
  }
}

bool FlappyBird::checkCollision() const {
  for (int i = 0; i < PIPE_COUNT; i++) {
    bool horizontalOverlap = (BIRD_X + BIRD_SIZE > pipes[i].x) && (BIRD_X < pipes[i].x + PIPE_WIDTH);
    if (!horizontalOverlap) continue;

    bool inGap = (birdY >= pipes[i].gapY) && (birdY + BIRD_SIZE <= pipes[i].gapY + PIPE_GAP);
    if (!inGap) return true;
  }
  return false;
}

void FlappyBird::drawPipes() {
  for (int i = 0; i < PIPE_COUNT; i++) {
    canvas.fillRect(pipes[i].x, 0, PIPE_WIDTH, pipes[i].gapY, TFT_GREEN);
    canvas.fillRect(pipes[i].x, pipes[i].gapY + PIPE_GAP, PIPE_WIDTH, 240 - (pipes[i].gapY + PIPE_GAP), TFT_GREEN);
  }
}

void FlappyBird::drawBird() {
  canvas.fillRect(BIRD_X, (int)birdY, BIRD_SIZE, BIRD_SIZE, TFT_YELLOW);
}

void FlappyBird::draw() {
  canvas.fillSprite(TFT_CYAN);
  drawPipes();
  drawBird();

  canvas.setTextColor(TFT_WHITE, TFT_CYAN);
  canvas.setTextSize(2);
  canvas.setCursor(10, 10);
  canvas.printf("Score: %d", score);

  if (gameOver) {
    canvas.setTextColor(TFT_RED, TFT_CYAN);
    canvas.setCursor(50, 110);
    canvas.print("GAME OVER");
  }

  canvas.pushSprite(0, 0);
}

bool FlappyBird::isGameOver() const {
  return gameOver;
}

int FlappyBird::getScore() const {
  return score;
}
