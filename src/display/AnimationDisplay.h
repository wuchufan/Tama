#pragma once
#include <TFT_eSPI.h>
#include "BackgroundDisplay.h"

class AnimationDisplay {
public:
  AnimationDisplay(TFT_eSPI& tft, BackgroundDisplay& background);

  void begin();
  void update();
  void draw();
  void playAnimation(const uint16_t* const frames[], int frameCount, unsigned long frameDelay, int repeatCount = 1);
  void playFeedAnimation();
  void setIdleMovement();
  bool isIdle() const;

private:
  TFT_eSprite character;
  TFT_eSPI& tft;
  BackgroundDisplay& background;
  static const unsigned long FRAME_DELAY;

  const uint16_t* const* activeFrames;
  int activeFrameCount;
  unsigned long activeFrameDelay;
  bool activeLoops;
  int animRepeatsRemaining;

  int frameIndex;
  unsigned long lastFrameTime;

  int posX;
  int moveDirection;
  static const int MOVE_MIN_X;
  int moveMaxX;    // computed in begin(), not at static-init time — depends on SPRITE_SIZE, defined in a different .cpp file
  static const int MOVE_STEP;
  static const int REGION_X;
  int regionWidth; // same reason as moveMaxX

  void returnToIdle();
};

