#include "AnimationDisplay.h"
#include "../Sprites.h"

const unsigned long AnimationDisplay::FRAME_DELAY = 150; // same cadence as animation.ino

const int AnimationDisplay::MOVE_MIN_X = 10;
const int AnimationDisplay::MOVE_STEP = 2;
const int AnimationDisplay::REGION_X = MOVE_MIN_X;

AnimationDisplay::AnimationDisplay(TFT_eSPI& tft, BackgroundDisplay& background)
  : character(&tft),
    tft(tft),
    background(background),
    activeFrames(idle_frames), activeFrameCount(IDLE_FRAME_COUNT), activeFrameDelay(FRAME_DELAY),
    activeLoops(true), animRepeatsRemaining(0),
    frameIndex(0), lastFrameTime(0),
    posX(MOVE_MIN_X), moveDirection(1),
    moveMaxX(0), regionWidth(0) {
}

void AnimationDisplay::begin() {
  // computed here, not as static const initializers — SPRITE_SIZE lives in Sprites.cpp,
  // a different translation unit, and C++ doesn't guarantee cross-file static init order.
  // begin() runs from setup(), which is only ever called after all static init completes.
  moveMaxX = min(130, 230 - SPRITE_SIZE[0]);   // keeps the 100px sprite on a ~240px-wide screen
  regionWidth = (moveMaxX - MOVE_MIN_X) + SPRITE_SIZE[0]; // covers the full walking corridor

  character.setColorDepth(16);     // RGB565
  character.createSprite(regionWidth, 100);
  character.setSwapBytes(true);
}

void AnimationDisplay::update() {
  if (millis() - lastFrameTime >= activeFrameDelay) {
    lastFrameTime = millis();

    if (activeLoops) {
      frameIndex = (frameIndex + 1) % activeFrameCount;

      setIdleMovement();
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
void AnimationDisplay::setIdleMovement(){
    posX += moveDirection * MOVE_STEP;
    if (posX <= MOVE_MIN_X || posX >= moveMaxX) {
      moveDirection = -moveDirection;
      posX = constrain(posX, MOVE_MIN_X, moveMaxX);
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
  playAnimation(smile_frames, SMILE_FRAME_COUNT, 80, 4);
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
  background.drawPatchInto(character, REGION_X, 20, regionWidth, 100);
  character.pushImage(posX - REGION_X, 0, 100, 100, const_cast<uint16_t*>(activeFrames[frameIndex]), TFT_BLACK); // TFT_BLACK pixels in the frame art are skipped (transparent), letting the background show through around the character's shape
  character.pushSprite(REGION_X, 20); // ONE real-screen transfer per frame
}
