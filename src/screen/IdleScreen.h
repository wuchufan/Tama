#pragma once
#include "Screen.h"
#include "ScreenManager.h"
#include "../display/AnimationDisplay.h"
#include "../display/BackgroundDisplay.h"

class IdleScreen : public Screen {
public:
  IdleScreen(AnimationDisplay& animator, BackgroundDisplay& background, ScreenManager& screens);

  void setStatsScreen(Screen& screen);
  void setMenuScreen(Screen& screen);

  void enter() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonB() override;
  void onButtonC() override;

private:
  AnimationDisplay& animator;
  BackgroundDisplay& background;
  ScreenManager& screens;
  Screen* statsScreen = nullptr;
  Screen* menuScreen = nullptr;
};
