#pragma once
#include "Screen.h"
#include "AnimationDisplay.h"

class IdleScreen : public Screen {
public:
  explicit IdleScreen(AnimationDisplay& animator);

  void update(const TamaState& tama, const EconomyManager& economy) override;

private:
  AnimationDisplay& animator;
};
