#include "IdleScreen.h"
#include "../menu/MenuActions.h" // for menuStack, mainMenu

IdleScreen::IdleScreen(AnimationDisplay& animatorRef, BackgroundDisplay& backgroundRef, ScreenManager& screensRef)
  : animator(animatorRef), background(backgroundRef), screens(screensRef) {
}

void IdleScreen::setStatsScreen(Screen& screen) { statsScreen = &screen; }
void IdleScreen::setMenuScreen(Screen& screen) { menuScreen = &screen; }

void IdleScreen::enter() {
  background.draw();
}

void IdleScreen::update(const TamaState& tama, const EconomyManager& economy) {
  animator.update();
}

void IdleScreen::onButtonB() {
  if (statsScreen) screens.switchTo(*statsScreen);
}

void IdleScreen::onButtonC() {
  menuStack.push(mainMenu);
  if (menuScreen) screens.switchTo(*menuScreen);
}
