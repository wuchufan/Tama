#include "MinigameScreen.h"

MinigameScreen::MinigameScreen(MinigameManager& minigamesRef, ScreenManager& screensRef, Screen& idleScreenRef)
  : minigames(minigamesRef), screens(screensRef), idleScreen(idleScreenRef) {
}

void MinigameScreen::playFlappyBird() {
  minigames.playFlappyBird();
  screens.switchTo(*this);
}

void MinigameScreen::update(const TamaState& tama, const EconomyManager& economy) {
  minigames.update();
  minigames.draw();
  if (minigames.isReadyToExit()) screens.switchTo(idleScreen);
}

void MinigameScreen::onButtonB() {
  minigames.primaryAction();
}

void MinigameScreen::onButtonC() {
  screens.switchTo(idleScreen); // manual exit
}
