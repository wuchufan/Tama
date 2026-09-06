#include "MenuDisplay.h"

MenuDisplay::MenuDisplay(TFT_eSprite& canvasRef)
  : canvas(canvasRef), lastDrawnScreen(nullptr), lastDrawnSelectedIndex(-1) {
}

void MenuDisplay::invalidate() {
  lastDrawnScreen = nullptr;
  lastDrawnSelectedIndex = -1;
}

void MenuDisplay::checkMenu(MenuStack& menuStack) {
  MenuWindow* screen = menuStack.current();
  bool screenChanged = (screen != lastDrawnScreen);

  if (screenChanged || screen->getSelectedIndex() != lastDrawnSelectedIndex) {
    if (menuStack.getDepth() == 1) {
      grid.draw(*screen, canvas);
    } else {
      list.draw(*screen, canvas);
    }
    canvas.pushSprite(0, 0);
    lastDrawnScreen = screen;
    lastDrawnSelectedIndex = screen->getSelectedIndex();
  }
}
