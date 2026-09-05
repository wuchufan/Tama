#include "TamaState.h"
#include "Config.h"
#include <Arduino.h>

TamaState::TamaState()
:food(Config::Tama::INITIAL_FOOD),
 happiness(Config::Tama::INITIAL_HAPPINESS),
 energy(Config::Tama::INITIAL_ENERGY),
 statusDropRate(Config::Tama::STATUS_DROP_RATE)
{}

void TamaState::update() {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate >= statusDropRate) {
    lastUpdate = millis();

    food = max(0, food - 1);
    happiness = max(0, happiness - 1);
    energy = max(0, energy - 1);
  }
}

void TamaState::feed() {
  food = min(100, food + 20);
  Serial.println("Tama feed pressed");
}

void TamaState::play() {
  if (energy >= 10) {
    happiness = min(100, happiness + 15);
    energy -= 10;
    food = max(0, food - 5);
  }
  Serial.println("Tama play pressed");
}

void TamaState::sleep() {
  energy = min(100, energy + 30);
  Serial.println("Tama sleep pressed");
}

void TamaState::clean() {

  Serial.println("Tama clean pressed");
}