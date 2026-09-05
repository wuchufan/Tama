#include "MenuActions.h"
#include "../TamaState.h"
#include "../CharacterManager.h"
#include "../EconomyManager.h"
#include "../minigames/FlappyBird.h"
#include "../display/DisplayManager.h"
#include <Arduino.h>

extern TamaState Tama;             // defined in main.cpp
extern CharacterManager Character; // defined in main.cpp
extern DisplayManager Display;     // defined in main.cpp
extern EconomyManager Economy;     // defined in main.cpp
extern FlappyBird FlappyBirdGame;  // defined in main.cpp
extern bool minigameActive;        // defined in main.cpp

static void onMainMenuAction(int id);
static void onActionsMenuAction(int id);
static void onDebugMenuAction(int id);
static void onShopMenuAction(int id);
static void onMinigamesMenuAction(int id);

const MenuItem mainMenuItems[] = {
  { "Actions",   onMainMenuAction, 0 },
  { "Debug",     onMainMenuAction, 1 },
  { "Shop",      onMainMenuAction, 2 },
  { "Minigames", onMainMenuAction, 3 },
  { "placeholder",   onMainMenuAction, 4 },
  { "placeholder",   onMainMenuAction, 5 },
  { "placeholder",   onMainMenuAction, 6 },
  { "placeholder",   onMainMenuAction, 7 },
  { "placeholder",   onMainMenuAction, 8 },

};
MenuScreen mainMenu(mainMenuItems, 9);

const MenuItem actionsMenuItems[] = {
  { "Feed",  onActionsMenuAction, 0 },
  { "Clean", onActionsMenuAction, 1 },
  { "Play",  onActionsMenuAction, 2 },
  { "Sleep", onActionsMenuAction, 3 },
  { "Back",  onActionsMenuAction, 4 },
};
MenuScreen actionsMenu(actionsMenuItems, 5);

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

const MenuItem shopMenuItems[] = {
  { "PlayStation",    onShopMenuAction, 0 },
  { "Shepherd's Pie", onShopMenuAction, 1 },
  { "Chips",          onShopMenuAction, 2 },
  { "Diet Coke",      onShopMenuAction, 3 },
  { "Back",           onShopMenuAction, 4 },
};
MenuScreen shopMenu(shopMenuItems, 5);

const MenuItem minigamesMenuItems[] = {
  { "Flappy Bird", onMinigamesMenuAction, 0 },
  { "Back",        onMinigamesMenuAction, 1 },
};
MenuScreen minigamesMenu(minigamesMenuItems, 2);

MenuStack menuStack;

void onMainMenuAction(int id) {
  switch (id) {
    case 0:
      menuStack.push(actionsMenu);
      break;
    case 1:
      menuStack.push(debugMenu);
      break;
    case 2:
      menuStack.push(shopMenu);
      break;
    case 3:
      menuStack.push(minigamesMenu);
      break;
    case 4:
      Serial.println("Not implemented yet");
      break;
    case 5:
      Serial.println("Not implemented yet");
      break;
    case 6:
      Serial.println("Not implemented yet");
      break;
    case 7:
      Serial.println("Not implemented yet");
      break;
    case 8:
      Serial.printf("Free heap: %.2f /  %.2f KB\n", ESP.getFreeHeap()/1024.0, ESP.getSketchSize()/1024.0);
      Serial.printf("Free sketch space: %.2f / %.2f KB\n", ESP.getFreeSketchSpace()/1024.0, ESP.getFlashChipSize()/1024.0);
      Serial.printf("PSRAM found: %s\n", psramFound() ? "yes" : "no");
      Serial.printf("Free PSRAM: %.2f KB\n", ESP.getFreePsram() / 1024.0);
      break;
  }
}

void onActionsMenuAction(int id) {
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
      menuStack.pop(); // Back
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

void onShopMenuAction(int id) {
  switch (id) {
    case 0:
      if (Economy.purchase(ShopItem::PLAYSTATION)) Serial.println("Bought PlayStation");
      else Serial.println("Not enough money");
      Serial.printf("Money: %d\n", Economy.getMoney());
      break;
    case 1:
      if (Economy.purchase(ShopItem::SHEPHERDS_PIE)) Serial.println("Bought Shepherd's Pie");
      else Serial.println("Not enough money");
      break;
    case 2:
      if (Economy.purchase(ShopItem::CHIPS)) Serial.println("Bought Chips");
      else Serial.println("Not enough money");
      break;
    case 3:
      if (Economy.purchase(ShopItem::DIET_COKE)) Serial.println("Bought Diet Coke");
      else Serial.println("Not enough money");
      break;
    case 4:
      menuStack.pop(); // Back
      break;
  }
}

void onMinigamesMenuAction(int id) {
  switch (id) {
    case 0:
      FlappyBirdGame.start();
      minigameActive = true;
      menuStack.closeAll();
      break;
    case 1:
      menuStack.pop(); // Back
      break;
  }
}
