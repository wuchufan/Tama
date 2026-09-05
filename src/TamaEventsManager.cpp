#include "TamaEventsManager.h"
#include "Config.h"
#include <Arduino.h>

const unsigned long TamaEventsManager::EVENT_CHECK_INTERVAL = Config::Events::CHECK_INTERVAL;
const int TamaEventsManager::EVENT_CHANCE_PERCENT = Config::Events::CHANCE_PERCENT;
const unsigned long TamaEventsManager::SICK_DURATION = Config::Events::SICK_DURATION;

TamaEventsManager::TamaEventsManager(TamaState& tamaRef, CharacterManager& characterRef)
  : tama(tamaRef), character(characterRef),
    lastEventCheckTime(0),
    sick(false), sickStartTime(0),
    pooped(false) {
}

void TamaEventsManager::update() {
  unsigned long now = millis();

  if (now - lastEventCheckTime >= EVENT_CHECK_INTERVAL) {
    lastEventCheckTime = now;
    triggerRandomEvent();
  }

  if (sick && (now - sickStartTime >= SICK_DURATION)) {
    sick = false;
  }
}

void TamaEventsManager::triggerRandomEvent() {
  if (random(100) >= EVENT_CHANCE_PERCENT) return; // no event this check

  TamaEvent event = static_cast<TamaEvent>(random(1, 5)); // SICK..PLAYED_WITH_TOYS
  applyEvent(event);
}

void TamaEventsManager::applyEvent(TamaEvent event) {
  switch (event) {
    case TamaEvent::SICK:
      sick = true;
      sickStartTime = millis();
      tama.energy = max(0, tama.energy - 20);
      Serial.println("[Event] Tama got sick!");
      break;

    case TamaEvent::POOPED:
      pooped = true;
      tama.cleanliness = max(0, tama.cleanliness - 20);
      Serial.println("[Event] Tama pooped!");
      break;

    case TamaEvent::UNHAPPY:
      tama.happiness = max(0, tama.happiness - 15);
      Serial.println("[Event] Tama is feeling unhappy.");
      break;

    case TamaEvent::PLAYED_WITH_TOYS:
      tama.happiness = min(100, tama.happiness + 10);
      character.modifyAttribute(Attribute::CURIOSITY, 1);
      Serial.println("[Event] Tama played with its toys and feels happy!");
      break;

    case TamaEvent::NONE:
      break;
  }
}

bool TamaEventsManager::isSick() const { return sick; }
bool TamaEventsManager::hasPooped() const { return pooped; }

void TamaEventsManager::cure()  { sick = false; }
void TamaEventsManager::clean() { pooped = false; }
