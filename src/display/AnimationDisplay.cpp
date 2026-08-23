#include "AnimationDisplay.h"
#include "../Sprites.h"

const unsigned long AnimationDisplay::FRAME_DELAY = 150; // same cadence as animation.ino

AnimationDisplay::AnimationDisplay(TFT_eSPI& tft)
  : character(&tft),
    activeFrames(idle_frames), activeFrameCount(IDLE_FRAME_COUNT), activeFrameDelay(FRAME_DELAY),
    activeLoops(true), animRepeatsRemaining(0),
    frameIndex(0), lastFrameTime(0) {
}

void AnimationDisplay::begin() {
  character.setColorDepth(16);     // RGB565
  character.createSprite(100, 100);
  character.setSwapBytes(true);
}

void AnimationDisplay::update() {
  if (millis() - lastFrameTime >= activeFrameDelay) {
    lastFrameTime = millis();

    if (activeLoops) {
      frameIndex = (frameIndex + 1) % activeFrameCount;
    } else {
      frameIndex++;
      if (frameIndex >= activeFrameCount) {
        frameIndex = 0;
        animRepeatsRemaining--;
        if (animRepeatsRemaining <= 0) {
          returnToIdle();
        }
      }
    }

    draw();
  }
}

void AnimationDisplay::playAnimation(const uint16_t* const frames[], int frameCount, unsigned long frameDelay, int repeatCount) {
  activeFrames = frames;
  activeFrameCount = frameCount;
  activeFrameDelay = frameDelay;
  activeLoops = false;
  animRepeatsRemaining = repeatCount;
  frameIndex = 0;
  lastFrameTime = millis();
}

void AnimationDisplay::playFeedAnimation() {
  playAnimation(idle_frames, IDLE_FRAME_COUNT, 80, 4);
}

bool AnimationDisplay::isIdle() const {
  return activeLoops;
}

void AnimationDisplay::returnToIdle() {
  activeFrames = idle_frames;
  activeFrameCount = IDLE_FRAME_COUNT;
  activeFrameDelay = FRAME_DELAY;
  activeLoops = true;
}

void AnimationDisplay::draw() {
  character.pushImage(0, 0, 100, 100, activeFrames[frameIndex]);
  character.pushSprite(50, 20); // placeholder position, tune to your panel
}
