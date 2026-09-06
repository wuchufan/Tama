#include "InputManager.h"
#include "TamaState.h"
#include "display/DisplayManager.h"
#include "CharacterManager.h"
#include "TamaEventsManager.h"
#include "EconomyManager.h"
#include "minigames/MinigameManager.h"
#include "screen/MinigameScreen.h"
#include "screen/IdleScreen.h"
#include "screen/StatsScreen.h"
#include "screen/MenuAppScreen.h"
#include "screen/ScreenManager.h"
#include "menu/MenuActions.h"

InputManager buttonA(1);
InputManager buttonB(2);
InputManager buttonC(3);

TamaState Tama;
DisplayManager Display;
CharacterManager Character;
TamaEventsManager Events(Tama, Character);
EconomyManager Economy;
MinigameManager Minigames(Display.getCanvas());

ScreenManager AppScreens;
IdleScreen idleScreen(Display, AppScreens);
MenuAppScreen menuAppScreen(Display, menuStack, AppScreens, idleScreen);
StatsScreen statsScreen(Display, AppScreens, idleScreen, menuAppScreen);
MinigameScreen minigameScreen(Minigames, AppScreens, idleScreen);

void setup() {
  Serial.begin(115200);
  Serial.println("Setup complete");

  Display.begin();
  Character.begin();

  idleScreen.setStatsScreen(statsScreen);
  idleScreen.setMenuScreen(menuAppScreen);

  buttonA.init();
  buttonB.init();
  buttonC.init();

  AppScreens.switchTo(idleScreen);
}

void loop() {
  Tama.update();
  Character.update();
  Events.update();

  if (buttonB.readButton()) AppScreens.onButtonB();
  if (buttonA.readButton()) AppScreens.onButtonA();
  if (buttonC.readButton()) AppScreens.onButtonC();

  AppScreens.update(Tama, Economy);
}
