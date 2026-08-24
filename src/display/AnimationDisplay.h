#pragma once
#include <TFT_eSPI.h>

class AnimationDisplay {
public:
  explicit AnimationDisplay(TFT_eSPI& tft);

  void begin();
  void update();
  void draw();
  void playAnimation(const uint16_t* const frames[], int frameCount, unsigned long frameDelay, int repeatCount = 1);
  void playFeedAnimation();
  void setIdleMotion();
  bool isIdle() const;

private:
  TFT_eSprite character;
  TFT_eSPI& tft;
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
  static const int MOVE_MAX_X;
  static const int MOVE_STEP;
  static const int REGION_X;
  static const int REGION_WIDTH;

  void returnToIdle();
};
