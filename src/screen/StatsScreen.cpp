#include "StatsScreen.h"
#include "../menu/MenuActions.h" // for menuStack, mainMenu

StatsScreen::StatsScreen(StatsDisplay& statsRef, BackgroundDisplay& backgroundRef, ScreenManager& screensRef, Screen& idleScreenRef, Screen& menuScreenRef)
  : stats(statsRef), background(backgroundRef), screens(screensRef), idleScreen(idleScreenRef), menuScreen(menuScreenRef) {
}

void StatsScreen::enter() {
  background.clearScreen(); // black backdrop for the stats screen
}

void StatsScreen::update(const TamaState& tama, const EconomyManager& economy) {
  stats.draw(tama, economy);
}

void StatsScreen::onButtonB() {
  screens.switchTo(idleScreen);
}

void StatsScreen::onButtonC() {
  menuStack.push(mainMenu);
  screens.switchTo(menuScreen);
}
