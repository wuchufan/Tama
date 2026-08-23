#include "CharacterManager.h"

const unsigned long CharacterManager::EGG_DURATION = 3000;      // 30s as egg (placeholder)
const unsigned long CharacterManager::INFANCY_DURATION = 3000; // 30s infancy (placeholder)
const unsigned long CharacterManager::PUBERTY_DURATION = 3000; // 30s puberty (placeholder)

CharacterManager::CharacterManager()
  : stage(GrowthStage::EGG), stageStartTime(0),
    social(0), courage(0), diligence(0), decency(0), curiosity(0) {
}

void CharacterManager::begin() {
  randomSeed(analogRead(0)); // seed from floating analog pin noise; pick an unused pin on your board
  rollRandomAttributes();
  stage = GrowthStage::EGG;
  stageStartTime = millis();
}

void CharacterManager::update() {
  tryAdvanceStage();
}

void CharacterManager::rollRandomAttributes() {
  social    = random(ATTR_MIN, ATTR_MAX + 1); // random(min, max) is exclusive of max
  courage   = random(ATTR_MIN, ATTR_MAX + 1);
  diligence = random(ATTR_MIN, ATTR_MAX + 1);
  decency   = random(ATTR_MIN, ATTR_MAX + 1);
  curiosity = random(ATTR_MIN, ATTR_MAX + 1);
}

void CharacterManager::tryAdvanceStage() {
  unsigned long elapsed = millis() - stageStartTime;

  switch (stage) {
    case GrowthStage::EGG:
      if (elapsed >= EGG_DURATION) {
        stage = GrowthStage::INFANCY;
        stageStartTime = millis();
        Serial.println("Tama hatched into Infancy.");
      }
      break;

    case GrowthStage::INFANCY:
      if (elapsed >= INFANCY_DURATION) {
        stage = GrowthStage::PUBERTY;
        stageStartTime = millis();
        Serial.println("Tama grew into Puberty.");
      }
      break;

    case GrowthStage::PUBERTY:
      if (elapsed >= PUBERTY_DURATION) {
        stage = GrowthStage::ADULT;
        stageStartTime = millis();
        Serial.println("Tama matured into Adulthood.");
      }
      break;

    case GrowthStage::ADULT:
      break; // terminal stage
  }
}

void CharacterManager::advanceStage() {
  switch (stage) {
    case GrowthStage::EGG:     stage = GrowthStage::INFANCY; break;
    case GrowthStage::INFANCY: stage = GrowthStage::PUBERTY; break;
    case GrowthStage::PUBERTY: stage = GrowthStage::ADULT;   break;
    case GrowthStage::ADULT:   break;
  }
  stageStartTime = millis();
}

int& CharacterManager::attributeRef(Attribute attr) {
  switch (attr) {
    case Attribute::SOCIAL:    return social;
    case Attribute::COURAGE:   return courage;
    case Attribute::DILIGENCE: return diligence;
    case Attribute::DECENCY:   return decency;
    default:                   return curiosity;
  }
}

void CharacterManager::modifyAttribute(Attribute attr, int delta) {
  int& value = attributeRef(attr);
  value = constrain(value + delta, ATTR_MIN, ATTR_MAX);
}

GrowthStage CharacterManager::getStage() const { return stage; }
int CharacterManager::getSocial() const    { return social; }
int CharacterManager::getCourage() const   { return courage; }
int CharacterManager::getDiligence() const { return diligence; }
int CharacterManager::getDecency() const   { return decency; }
int CharacterManager::getCuriosity() const { return curiosity; }
bool CharacterManager::isExtrovert() const { return social > 10; }
