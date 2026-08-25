#include "AnimationDisplay.h"
#include "../Sprites.h"

const unsigned long AnimationDisplay::FRAME_DELAY = 150; // same cadence as animation.ino

const int AnimationDisplay::LEFTMOST_X = 10; // this is the left most position character can be
const int AnimationDisplay::MOVE_STEP = 2;
const int AnimationDisplay::MOTION_CORRIDOR_X = LEFTMOST_X;

AnimationDisplay::AnimationDisplay(TFT_eSPI& tft, BackgroundDisplay& background)
  : character(&tft),
    characterFrame(&tft),
    tft(tft),
    background(background),
    activeFrames(idle_frames), activeFrameCount(IDLE_FRAME_COUNT), activeFrameDelay(FRAME_DELAY),
    activeLoops(true), animRepeatsRemaining(0),
    frameIndex(0), lastFrameTime(0),
    currentXPos(LEFTMOST_X), currentYPos(120), moveDirection(1),
    rightMostX(0), motionCorridorWidth(0) {
}

void AnimationDisplay::begin() {
  // computed here, not at static-init time, to avoid cross-file init-order issues with SPRITE_SIZE
  rightMostX = min(130, 230 - SPRITE_SIZE[0]);   // keeps the 100px sprite on a ~240px-wide screen
  motionCorridorWidth = (rightMostX - LEFTMOST_X) + SPRITE_SIZE[0]; // covers the full walking corridor

  character.setColorDepth(16);     // RGB565

  // Allocates character's off-screen pixel buffer (RAM only, invisible until pushSprite()
  // sends it to the real screen). Required before any pushImage/fillSprite call on character.
  character.createSprite(motionCorridorWidth, 100);
  character.setSwapBytes(true);

  characterFrame.setColorDepth(16);
  characterFrame.createSprite(100, 100);
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
    currentXPos += moveDirection * MOVE_STEP;
    if (currentXPos <= LEFTMOST_X || currentXPos >= rightMostX) {
      moveDirection = -moveDirection;
      currentXPos = constrain(currentXPos, LEFTMOST_X, rightMostX);
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
  // playAnimation(smile_frames, SMILE_FRAME_COUNT, 80, 4);
  playAnimation(cry_frames, CRY_FRAME_COUNT, 150, 4);
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
  background.drawPatchInto(character, MOTION_CORRIDOR_X, currentYPos, motionCorridorWidth, 100);

  // load the current frame's raw data into its own sprite, then use the library's real
  // sprite-to-sprite transparency 
  characterFrame.pushImage(0, 0, 100, 100, const_cast<uint16_t*>(activeFrames[frameIndex]));
  characterFrame.pushToSprite(&character, currentXPos - MOTION_CORRIDOR_X, 0, TFT_BLACK);

  character.pushSprite(MOTION_CORRIDOR_X, currentYPos); // ONE real-screen transfer per frame
}
