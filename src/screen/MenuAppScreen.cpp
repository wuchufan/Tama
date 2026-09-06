#include "MenuAppScreen.h"

MenuAppScreen::MenuAppScreen(DisplayManager& displayRef, MenuStack& menuStackRef, ScreenManager& screensRef, Screen& idleScreenRef)
  : display(displayRef), menuStack(menuStackRef), screens(screensRef), idleScreen(idleScreenRef) {
}

void MenuAppScreen::enter() {
  display.invalidateMenu(); // the menu may be reopening on the same screen and selection
}

void MenuAppScreen::update(const TamaState& tama, const EconomyManager& economy) {
  display.checkDisplayMenu(menuStack);
}

void MenuAppScreen::onButtonA() { menuStack.current()->select(); }
void MenuAppScreen::onButtonB() { menuStack.current()->next(); }

void MenuAppScreen::onButtonC() {
  menuStack.closeAll();
  screens.switchTo(idleScreen);
}
