#include "MenuDisplay.h"

MenuDisplay::MenuDisplay(TFT_eSPI& tftRef, AnimationDisplay& animatorRef, StatsDisplay& statsRef)
  : tft(tftRef), animator(animatorRef), stats(statsRef),
    wasMenuOpen(false), lastDrawnScreen(nullptr), lastDrawnSelectedIndex(-1) {
}

void MenuDisplay::checkMenu(const TamaState& tama, MenuStack& menuStack) {
  if (!menuStack.isOpen()) {
    if (wasMenuOpen) {
      tft.fillScreen(TFT_BLACK);
      animator.draw();
      if (animator.isIdle()) {
        stats.draw(tama);
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
    drawItemList(*screen);
    lastDrawnScreen = screen;
    lastDrawnSelectedIndex = screen->getSelectedIndex();
  }
  wasMenuOpen = true;
}

void MenuDisplay::drawItemList(MenuScreen& screen) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);

  for (int i = 0; i < screen.getItemCount(); i++) {
    tft.setTextColor(i == screen.getSelectedIndex() ? TFT_YELLOW : TFT_WHITE, TFT_BLACK);
    tft.setCursor(10, 20 + i * 22);
    tft.printf("%s%s", i == screen.getSelectedIndex() ? "-> " : "   ", screen.getLabel(i));
  }
}
