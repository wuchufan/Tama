#include "IdleScreen.h"
#include "../menu/MenuActions.h" // for menuStack, mainMenu

IdleScreen::IdleScreen(DisplayManager& displayRef, ScreenManager& screensRef)
  : display(displayRef), screens(screensRef) {
}

void IdleScreen::setStatsScreen(Screen& screen) { statsScreen = &screen; }
void IdleScreen::setMenuScreen(Screen& screen) { menuScreen = &screen; }

void IdleScreen::enter() {
  display.refreshBackground();
}

void IdleScreen::update(const TamaState& tama, const EconomyManager& economy) {
  display.updateAnimation();
}

void IdleScreen::onButtonB() {
  if (statsScreen) screens.switchTo(*statsScreen);
}

void IdleScreen::onButtonC() {
  menuStack.push(mainMenu);
  if (menuScreen) screens.switchTo(*menuScreen);
}
