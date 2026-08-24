#include "AnimationDisplay.h"
#include "../Sprites.h"

const unsigned long AnimationDisplay::FRAME_DELAY = 150; // same cadence as animation.ino

const int AnimationDisplay::MOVE_MIN_X = 10;
const int AnimationDisplay::MOVE_MAX_X = 130;  // keeps the 100px sprite on a ~240px-wide screen
const int AnimationDisplay::MOVE_STEP = 2;
const int AnimationDisplay::REGION_X = MOVE_MIN_X;
const int AnimationDisplay::REGION_WIDTH = (MOVE_MAX_X - MOVE_MIN_X) + SPRITE_SIZE[0]; // covers the full walking corridor

AnimationDisplay::AnimationDisplay(TFT_eSPI& tft)
  : character(&tft),
    tft(tft),
    activeFrames(idle_frames), activeFrameCount(IDLE_FRAME_COUNT), activeFrameDelay(FRAME_DELAY),
    activeLoops(true), animRepeatsRemaining(0),
    frameIndex(0), lastFrameTime(0),
    posX(MOVE_MIN_X), moveDirection(1) {
}

void AnimationDisplay::begin() {
  character.setColorDepth(16);     // RGB565
  character.createSprite(REGION_WIDTH, 100);
  character.setSwapBytes(true);
}

void AnimationDisplay::update() {
  if (millis() - lastFrameTime >= activeFrameDelay) {
    lastFrameTime = millis();

    if (activeLoops) {
      frameIndex = (frameIndex + 1) % activeFrameCount;

      setIdleMotion();
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
void AnimationDisplay::setIdleMotion(){
    posX += moveDirection * MOVE_STEP;
    if (posX <= MOVE_MIN_X || posX >= MOVE_MAX_X) {
      moveDirection = -moveDirection;
      posX = constrain(posX, MOVE_MIN_X, MOVE_MAX_X);
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
  character.fillSprite(TFT_BLACK);                                            // clear the off-screen buffer only — invisible
  character.pushImage(posX - REGION_X, 0, 100, 100, activeFrames[frameIndex]); // draw character at its position within the region
  character.pushSprite(REGION_X, 20);                                         // ONE real-screen transfer per frame
}
