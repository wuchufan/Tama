#include "MinigameScreen.h"

MinigameScreen::MinigameScreen(MinigameManager& minigamesRef, ScreenManager& screensRef, Screen& normalScreenRef)
  : minigames(minigamesRef), screens(screensRef), normalScreen(normalScreenRef) {
}

void MinigameScreen::update(const TamaState& tama, const EconomyManager& economy) {
  minigames.update();
  minigames.draw();
  if (minigames.isReadyToExit()) screens.switchTo(normalScreen);
}

void MinigameScreen::onButtonB() {
  minigames.primaryAction();
}

void MinigameScreen::onButtonC() {
  screens.switchTo(normalScreen); // manual exit
}
