#include "MenuAppScreen.h"

MenuAppScreen::MenuAppScreen(MenuDisplay& menuDisplayRef, MenuStack& menuStackRef, ScreenManager& screensRef, Screen& idleScreenRef)
  : menuDisplay(menuDisplayRef), menuStack(menuStackRef), screens(screensRef), idleScreen(idleScreenRef) {
}

void MenuAppScreen::enter() {
  menuDisplay.invalidate(); // the menu may be reopening on the same screen and selection
}

void MenuAppScreen::update(const TamaState& tama, const EconomyManager& economy) {
  menuDisplay.checkMenu(menuStack);
}

void MenuAppScreen::onButtonA() { menuStack.current()->select(); }
void MenuAppScreen::onButtonB() { menuStack.current()->next(); }

void MenuAppScreen::onButtonC() {
  menuStack.closeAll();
  screens.switchTo(idleScreen);
}
