#include "IdleScreen.h"

IdleScreen::IdleScreen(AnimationDisplay& animatorRef) : animator(animatorRef) {
}

void IdleScreen::update(const TamaState& tama, const EconomyManager& economy) {
  animator.update();
}
