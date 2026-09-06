#include "TamaFans.h"
#include "../Sprites.h"
#include <Arduino.h>

namespace {
  constexpr int TAMA_X = 70;
  constexpr int TAMA_Y = 80;
  constexpr int TAMA_SIZE = 100;

  constexpr int FAN_W = 44;
  constexpr int FAN_H = 60;
  constexpr int FAN_Y = 120;
  constexpr int FAN_LEFT_X = 8;
  constexpr int FAN_RIGHT_X = 240 - FAN_W - 8;

  constexpr int BUBBLE_W = 34;
  constexpr int BUBBLE_H = 30;
  constexpr int BUBBLE_GAP = 8;

  constexpr unsigned long START_DURATION = 1600; // ms to answer the first fan
  constexpr unsigned long MIN_DURATION = 600;    // fastest the window ever gets
  constexpr unsigned long SPEEDUP_STEP = 40;     // ms shaved off per fan served

  constexpr int BUG_PERCENT = 20; // share of fans that are bugs, not real fans
}

TamaFans::TamaFans(TFT_eSprite& canvasRef)
  : canvas(canvasRef), fanOnLeft(true), wish(Wish::AUTOGRAPH),
    fanArrivedTime(0), fanDuration(START_DURATION), gameOver(false), score(0) {
}

void TamaFans::start() {
  gameOver = false;
  score = 0;
  nextFan();
}

void TamaFans::nextFan() {
  fanOnLeft = (random(2) == 0);

  if (random(100) < BUG_PERCENT) {
    wish = Wish::BUG;
  } else {
    wish = (random(2) == 0) ? Wish::AUTOGRAPH : Wish::MAIL;
  }

  long window = (long)START_DURATION - (long)score * SPEEDUP_STEP;
  fanDuration = window < (long)MIN_DURATION ? MIN_DURATION : (unsigned long)window;
  fanArrivedTime = millis();
}

void TamaFans::answer(bool leftSide) {
  if (gameOver) return;

  if (leftSide != fanOnLeft || wish == Wish::BUG) {
    gameOver = true; // wrong side, or fell for a bug
    return;
  }

  score++;
  nextFan();
}

void TamaFans::actionB()   { answer(false); }
void TamaFans::actionA() { answer(true); }

void TamaFans::update() {
  if (gameOver) return;

  if (millis() - fanArrivedTime >= fanDuration) {
    if (wish == Wish::BUG) {
      score++; // bugs leave on their own — ignoring one counts
      nextFan();
    } else {
      gameOver = true; // left a real fan waiting
    }
  }
}

void TamaFans::drawFan(int x) {
  uint16_t bodyColor = (wish == Wish::BUG) ? TFT_MAROON : TFT_BLUE;
  canvas.fillRoundRect(x, FAN_Y, FAN_W, FAN_H, 6, bodyColor);

  int bubbleX = x + (FAN_W - BUBBLE_W) / 2;
  int bubbleY = FAN_Y - BUBBLE_H - BUBBLE_GAP;
  canvas.fillRoundRect(bubbleX, bubbleY, BUBBLE_W, BUBBLE_H, 8, TFT_WHITE);

  const char* glyph = "A";
  uint16_t glyphColor = TFT_BLACK;
  if (wish == Wish::MAIL) {
    glyph = "M";
  } else if (wish == Wish::BUG) {
    glyph = "X";
    glyphColor = TFT_RED;
  }

  canvas.setTextSize(2);
  canvas.setTextColor(glyphColor, TFT_WHITE);
  canvas.setCursor(bubbleX + (BUBBLE_W - canvas.textWidth(glyph)) / 2, bubbleY + (BUBBLE_H - 16) / 2);
  canvas.print(glyph);
}

void TamaFans::draw() {
  canvas.fillSprite(TFT_BLACK);

  canvas.pushImage(TAMA_X, TAMA_Y, TAMA_SIZE, TAMA_SIZE, const_cast<uint16_t*>(idle_0));

  drawFan(fanOnLeft ? FAN_LEFT_X : FAN_RIGHT_X);

  canvas.setTextSize(2);
  canvas.setTextColor(TFT_WHITE, TFT_BLACK);
  canvas.setCursor(10, 10);
  canvas.printf("Fans: %d", score);

  unsigned long elapsed = millis() - fanArrivedTime;
  int barWidth = 220 - (int)((elapsed * 220) / fanDuration);
  if (barWidth < 0) barWidth = 0;
  canvas.fillRect(10, 40, barWidth, 6, TFT_GREEN);

  if (gameOver) {
    canvas.setTextColor(TFT_RED, TFT_BLACK);
    canvas.setCursor(50, 200);
    canvas.print("GAME OVER");
  }

  canvas.pushSprite(0, 0);
}

bool TamaFans::isGameOver() const {
  return gameOver;
}

int TamaFans::getScore() const {
  return score;
}
