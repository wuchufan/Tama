#pragma once
#include "Screen.h"
#include "ScreenManager.h"
#include "../minigames/MinigameManager.h"

class MinigameScreen : public Screen {
public:
  MinigameScreen(MinigameManager& minigames, ScreenManager& screens, Screen& idleScreen);

  void playFlappyBird(); // starts the game and shows this screen
  void playTamaFans();

  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonA() override;
  void onButtonB() override;
  void onButtonC() override;

private:
  MinigameManager& minigames;
  ScreenManager& screens;
  Screen& idleScreen;
};
