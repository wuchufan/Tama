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
  TFT_eSprite characterFrame; // holds the current frame's raw data so it becomes a real sprite, since pushToSprite() needs a sprite source, not a raw pointer
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

  int currentXPos;
  int currentYPos;
  int moveDirection;
  static const int LEFTMOST_X;
  int rightMostX;    // computed in begin(), not at static-init time — depends on SPRITE_SIZE, defined in a different .cpp file
  static const int MOVE_STEP;
  static const int MOTION_CORRIDOR_X;
  int motionCorridorWidth; // same reason as rightMostX

  void returnToIdle();
};

