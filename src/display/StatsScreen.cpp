#include "StatsScreen.h"

StatsScreen::StatsScreen(StatsDisplay& statsRef, BackgroundDisplay& backgroundRef)
  : stats(statsRef), background(backgroundRef) {
}

void StatsScreen::enter() {
  background.clearScreen(); // black backdrop for the stats screen
}

void StatsScreen::exit() {
  background.draw(); // restore the wallpaper before resuming the walking animation
}

void StatsScreen::update(const TamaState& tama, const EconomyManager& economy) {
  stats.draw(tama, economy);
}
