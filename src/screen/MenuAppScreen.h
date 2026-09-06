#pragma once
#include "Screen.h"
#include "ScreenManager.h"
#include "../display/DisplayManager.h"
#include "../menu/MenuStack.h"

class MenuAppScreen : public Screen {
public:
  MenuAppScreen(DisplayManager& display, MenuStack& menuStack, ScreenManager& screens, Screen& idleScreen);

  void enter() override;
  void update(const TamaState& tama, const EconomyManager& economy) override;
  void onButtonA() override;
  void onButtonB() override;
  void onButtonC() override;

private:
  DisplayManager& display;
  MenuStack& menuStack;
  ScreenManager& screens;
  Screen& idleScreen;
};
