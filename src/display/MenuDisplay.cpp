#include "MenuDisplay.h"

MenuDisplay::MenuDisplay(TFT_eSPI& tftRef, BackgroundDisplay& backgroundRef, AnimationDisplay& animatorRef, StatsDisplay& statsRef)
  : tft(tftRef), background(backgroundRef), animator(animatorRef), stats(statsRef), canvas(&tftRef),
    wasMenuOpen(false), lastDrawnScreen(nullptr), lastDrawnSelectedIndex(-1) {
}

void MenuDisplay::begin() {
  canvas.setColorDepth(16);
  canvas.createSprite(240, 240);
  canvas.setSwapBytes(true);
}

void MenuDisplay::checkMenu(const TamaState& tama, MenuStack& menuStack) {
  if (!menuStack.isOpen()) {
    if (wasMenuOpen) {
      background.draw();
      animator.draw();
      if (animator.isIdle()) {
        // stats.draw(tama);
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

  if (justOpened || screenChanged || screen->getSelectedIndex() != lastDrawnSelectedIndex) {
    if (menuStack.getDepth() == 1) {
      grid.draw(*screen, canvas);  // top level: icons only, 3x3
    } else {
      list.draw(*screen, canvas);  // any submenu: pill-list bubbles
    }
    canvas.pushSprite(0, 0);
    lastDrawnScreen = screen;
    lastDrawnSelectedIndex = screen->getSelectedIndex();
  }
  wasMenuOpen = true;
}
