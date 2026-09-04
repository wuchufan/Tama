#include "MenuDisplay.h"

MenuDisplay::MenuDisplay(TFT_eSPI& tftRef, BackgroundDisplay& backgroundRef, AnimationDisplay& animatorRef, StatsDisplay& statsRef)
  : tft(tftRef), background(backgroundRef), animator(animatorRef), stats(statsRef), grid(tftRef), list(tftRef),
    wasMenuOpen(false), lastDrawnScreen(nullptr), lastDrawnSelectedIndex(-1) {
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
      grid.draw(*screen);  // top level: icons only, 3x3
    } else {
      list.draw(*screen);  // any submenu: pill-list bubbles
    }
    lastDrawnScreen = screen;
    lastDrawnSelectedIndex = screen->getSelectedIndex();
  }
  wasMenuOpen = true;
}
