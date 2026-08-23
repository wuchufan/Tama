#include "DisplayManager.h"
#include "Sprites.h"

const unsigned long DisplayManager::FRAME_DELAY = 150; // same cadence as animation.ino

DisplayManager::DisplayManager()
  : character(&tft),
    activeFrames(idle_frames), activeFrameCount(IDLE_FRAME_COUNT), activeFrameDelay(FRAME_DELAY),
    activeLoops(true), animRepeatsRemaining(0),
    frameIndex(0), lastFrameTime(0),
    wasMenuOpen(false), lastDrawnScreen(nullptr), lastDrawnSelectedIndex(-1) {
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  character.setColorDepth(16);     // RGB565
  character.createSprite(100, 100);
  character.setSwapBytes(true);
}

void DisplayManager::update(const TamaState& tama) {
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

    drawCharacter();
  }
  if (activeLoops) {
    drawStats(tama);
  }
}

void DisplayManager::playAnimation(const uint16_t* const frames[], int frameCount, unsigned long frameDelay, int repeatCount) {
  activeFrames = frames;
  activeFrameCount = frameCount;
  activeFrameDelay = frameDelay;
  activeLoops = false;
  animRepeatsRemaining = repeatCount;
  frameIndex = 0;
  lastFrameTime = millis();
}

void DisplayManager::playFeedAnimation() {
  playAnimation(idle_frames, IDLE_FRAME_COUNT, 80, 4);
}

void DisplayManager::returnToIdle() {
  activeFrames = idle_frames;
  activeFrameCount = IDLE_FRAME_COUNT;
  activeFrameDelay = FRAME_DELAY;
  activeLoops = true;
}

void DisplayManager::checkMenu(const TamaState& tama, MenuStack& menuStack) {
  if (!menuStack.isOpen()) {
    if (wasMenuOpen) {
      // just closed: wipe the menu screen and force one fresh draw of the home screen
      tft.fillScreen(TFT_BLACK);
      drawCharacter();
      if (activeLoops) {
        drawStats(tama);
      }
      wasMenuOpen = false;
      lastDrawnScreen = nullptr;
      lastDrawnSelectedIndex = -1;
    }
    return;
  }

  MenuScreen* screen = menuStack.current();
  bool justOpened = !wasMenuOpen;
  bool screenChanged = (screen != lastDrawnScreen);

  // redraw only when it just opened, the screen changed (push/pop), or selection moved
  if (justOpened || screenChanged || screen->getSelectedIndex() != lastDrawnSelectedIndex) {
    drawItemList(*screen);
    lastDrawnScreen = screen;
    lastDrawnSelectedIndex = screen->getSelectedIndex();
  }
  wasMenuOpen = true;
}

void DisplayManager::drawItemList(MenuScreen& screen) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);

  for (int i = 0; i < screen.getItemCount(); i++) {
    tft.setTextColor(i == screen.getSelectedIndex() ? TFT_YELLOW : TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 20 + i * 22);
    tft.printf("%s%s", i == screen.getSelectedIndex() ? "-> " : "   ", screen.getLabel(i));
  }
}

void DisplayManager::drawCharacter() {
  character.pushImage(0, 0, 100, 100, activeFrames[frameIndex]);
  character.pushSprite(50, 20); // placeholder position, tune to your panel
}

void DisplayManager::drawStats(const TamaState& tama) {
  tft.setTextSize(2);

  drawStat(10, 130, "Food", tama.food);
  drawStat(10, 152, "Happy", tama.happiness);
  drawStat(10, 174, "Energy", tama.energy);
  drawStat(10, 196, "Clean", tama.cleanliness);
}

void DisplayManager::drawStat(int x, int y, const char* label, int value) {
  tft.setTextColor(value <= 20 ? TFT_RED : TFT_WHITE, TFT_BLACK);
  tft.setCursor(x, y);
  tft.printf("%s:%d  ", label, value);
}
