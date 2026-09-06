#include "MinigameScreen.h"

MinigameScreen::MinigameScreen(MinigameManager& minigamesRef, ScreenManager& screensRef, Screen& idleScreenRef)
  : minigames(minigamesRef), screens(screensRef), idleScreen(idleScreenRef) {
}

void MinigameScreen::playFlappyBird() {
  minigames.playFlappyBird();
  screens.switchTo(*this);
}

void MinigameScreen::playTamaFans() {
  minigames.playTamaFans();
  screens.switchTo(*this);
}

void MinigameScreen::update(const TamaState& tama, const EconomyManager& economy) {
  minigames.update();
  minigames.draw();
  if (minigames.isReadyToExit()) screens.switchTo(idleScreen);
}

void MinigameScreen::onButtonA() {
  minigames.actionA();
}

void MinigameScreen::onButtonB() {
  minigames.actionB();
}

void MinigameScreen::onButtonC() {
  screens.switchTo(idleScreen); // manual exit
}
