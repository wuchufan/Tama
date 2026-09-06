#include "StatsScreen.h"
#include "../menu/MenuActions.h" // for menuStack, mainMenu

StatsScreen::StatsScreen(DisplayManager& displayRef, ScreenManager& screensRef, Screen& idleScreenRef, Screen& menuScreenRef)
  : display(displayRef), screens(screensRef), idleScreen(idleScreenRef), menuScreen(menuScreenRef) {
}

void StatsScreen::enter() {
  display.clearScreen(); // black backdrop for the stats screen
}

void StatsScreen::update(const TamaState& tama, const EconomyManager& economy) {
  display.drawStats(tama, economy);
}

void StatsScreen::onButtonB() {
  screens.switchTo(idleScreen);
}

void StatsScreen::onButtonC() {
  menuStack.push(mainMenu);
  screens.switchTo(menuScreen);
}
