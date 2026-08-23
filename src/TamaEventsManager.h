#pragma once
#include "TamaState.h"
#include "CharacterManager.h"

enum class TamaEvent {
  NONE,
  SICK,
  POOPED,
  UNHAPPY,
  PLAYED_WITH_TOYS
};

class TamaEventsManager {
public:
  TamaEventsManager(TamaState& tama, CharacterManager& character);

  void update(); // call every loop(); occasionally rolls and applies an event

  bool isSick() const;
  bool hasPooped() const;

  void cure();  // clears isSick — hook for a future "give medicine" action
  void clean(); // clears hasPooped — hook for wiring into the existing Clean menu action

private:
  TamaState& tama;
  CharacterManager& character;

  unsigned long lastEventCheckTime;
  static const unsigned long EVENT_CHECK_INTERVAL;
  static const int EVENT_CHANCE_PERCENT;

  bool sick;
  unsigned long sickStartTime;
  static const unsigned long SICK_DURATION;

  bool pooped;

  void triggerRandomEvent();
  void applyEvent(TamaEvent event);
};
