#pragma once
#include <Arduino.h>

enum class GrowthStage {
  EGG,
  INFANCY,
  PUBERTY,
  ADULT
};

enum class Attribute {
  SOCIAL,     // S: 1-10 introvert, 11-20 extrovert
  COURAGE,    // C: bravery
  DILIGENCE,  // D: diligence vs laziness
  DECENCY,    // E: kindness vs meanness
  CURIOSITY   // U: tendency to explore
};

class CharacterManager {
public:
  CharacterManager();

  void begin();   // call from setup() — seeds RNG, rolls egg-stage attributes
  void update();  // call every loop() — ages the character, advances stages

  GrowthStage getStage() const;
  void advanceStage(); // manual override, e.g. for testing/debug button

  int getSocial() const;
  int getCourage() const;
  int getDiligence() const;
  int getDecency() const;
  int getCuriosity() const;
  bool isExtrovert() const; // derived from social > 10

  void modifyAttribute(Attribute attr, int delta); // events call this; clamps to [ATTR_MIN, ATTR_MAX]

  static const int ATTR_MIN = 1;
  static const int ATTR_MAX = 20;

private:
  GrowthStage stage;
  unsigned long stageStartTime;

  int social;
  int courage;
  int diligence;
  int decency;
  int curiosity;

  static const unsigned long EGG_DURATION;
  static const unsigned long INFANCY_DURATION;
  static const unsigned long PUBERTY_DURATION;

  int& attributeRef(Attribute attr);
  void rollRandomAttributes();
  void tryAdvanceStage();
};
