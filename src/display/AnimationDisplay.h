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
  bool isIdle() const;

private:
  TFT_eSprite character;
  static const unsigned long FRAME_DELAY;

  const uint16_t* const* activeFrames;
  int activeFrameCount;
  unsigned long activeFrameDelay;
  bool activeLoops;
  int animRepeatsRemaining;

  int frameIndex;
  unsigned long lastFrameTime;

  void returnToIdle();
};
