#include "InputManager.h"
#include "TamaState.h"
#include "display/DisplayManager.h"
#include "CharacterManager.h"
#include "TamaEventsManager.h"
#include "EconomyManager.h"
#include "minigames/MinigameManager.h"
#include "minigames/MinigameScreen.h"
#include "NormalDisplayScreen.h"
#include "display/ScreenManager.h"
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
NormalDisplayScreen normalScreen(Display);
MinigameScreen minigameScreen(Minigames, AppScreens, normalScreen);

void setup() {
  Serial.begin(115200);
  Serial.println("Setup complete");

  Display.begin();
  Character.begin();

  buttonA.init();
  buttonB.init();
  buttonC.init();

  AppScreens.switchTo(normalScreen);
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
