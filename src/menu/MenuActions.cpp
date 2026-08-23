#include "MenuActions.h"
#include "../TamaState.h"
#include "../CharacterManager.h"
#include "../display/DisplayManager.h"
#include <Arduino.h>

extern TamaState Tama;             // defined in main.cpp
extern CharacterManager Character; // defined in main.cpp
extern DisplayManager Display;     // defined in main.cpp

static void onMainMenuAction(int id);
static void onDebugMenuAction(int id);

const MenuItem mainMenuItems[] = {
  { "Feed",  onMainMenuAction, 0 },
  { "Clean", onMainMenuAction, 1 },
  { "Play",  onMainMenuAction, 2 },
  { "Sleep", onMainMenuAction, 3 },
  { "Debug", onMainMenuAction, 4 },
};
MenuScreen mainMenu(mainMenuItems, 5);

const MenuItem debugMenuItems[] = {
  { "Social",    onDebugMenuAction, 0 },
  { "Courage",   onDebugMenuAction, 1 },
  { "Diligence", onDebugMenuAction, 2 },
  { "Decency",   onDebugMenuAction, 3 },
  { "Curiosity", onDebugMenuAction, 4 },
  { "Stage",     onDebugMenuAction, 5 },
  { "Back",      onDebugMenuAction, 6 },
};
MenuScreen debugMenu(debugMenuItems, 7);

MenuStack menuStack;

void onMainMenuAction(int id) {
  switch (id) {
    case 0:
      Tama.feed();
      Display.playFeedAnimation();
      menuStack.closeAll();
      break;
    case 1:
      Tama.clean();
      menuStack.closeAll();
      break;
    case 2:
      Tama.play();
      menuStack.closeAll();
      break;
    case 3:
      Tama.sleep();
      menuStack.closeAll();
      break;
    case 4:
      menuStack.push(debugMenu);
      break;
  }
}

void onDebugMenuAction(int id) {
  switch (id) {
    case 0: Serial.printf("[Debug] Social: %d (%s)\n", Character.getSocial(), Character.isExtrovert() ? "Extrovert" : "Introvert"); break;
    case 1: Serial.printf("[Debug] Courage: %d\n", Character.getCourage()); break;
    case 2: Serial.printf("[Debug] Diligence: %d\n", Character.getDiligence()); break;
    case 3: Serial.printf("[Debug] Decency: %d\n", Character.getDecency()); break;
    case 4: Serial.printf("[Debug] Curiosity: %d\n", Character.getCuriosity()); break;
    case 5: {
      const char* stageNames[] = { "Egg", "Infancy", "Puberty", "Adult" };
      Serial.printf("[Debug] Stage: %s\n", stageNames[(int)Character.getStage()]);
      break;
    }
    case 6: menuStack.pop(); break;
  }
}
