#include "NormalDisplayScreen.h"
#include "menu/MenuActions.h" // for menuStack, mainMenu

NormalDisplayScreen::NormalDisplayScreen(DisplayManager& displayRef) : display(displayRef) {
}

void NormalDisplayScreen::enter() {
  display.refreshBackground(); // wipe whatever the minigame left on the real screen
}

void NormalDisplayScreen::update(const TamaState& tama, const EconomyManager& economy) {
  if (!menuStack.isOpen()) {
    display.update(tama, economy);
  }
  display.checkDisplayMenu(tama, menuStack);
}

void NormalDisplayScreen::onButtonA() {
  if (menuStack.isOpen()) menuStack.current()->select();
}

void NormalDisplayScreen::onButtonB() {
  if (menuStack.isOpen()) {
    menuStack.current()->next();
  } else {
    display.toggleStatsScreen();
  }
}

void NormalDisplayScreen::onButtonC() {
  if (menuStack.isOpen()) {
    menuStack.closeAll();
  } else {
    menuStack.push(mainMenu);
  }
}
