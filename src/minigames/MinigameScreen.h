#pragma once
#include "../display/Screen.h"
#include "../display/ScreenManager.h"
#include "MinigameManager.h"

class MinigameScreen : public Screen {
public:
  MinigameScreen(MinigameManager& minigames, ScreenManager& screens, Screen& normalScreen);

  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonB() override;
  void onButtonC() override;

private:
  MinigameManager& minigames;
  ScreenManager& screens;
  Screen& normalScreen;
};
