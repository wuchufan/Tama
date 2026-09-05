#include "InputManager.h"
#include "TamaState.h"
#include "display/DisplayManager.h"
#include "CharacterManager.h"
#include "TamaEventsManager.h"
#include "EconomyManager.h"
#include "minigames/MinigameManager.h"
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

void setup() {
  Serial.begin(115200);
  Serial.println("Setup complete");

  Display.begin();
  Character.begin();

  buttonA.init();
  buttonB.init();
  buttonC.init();
}

void loop() {
  Tama.update();
  Character.update();
  Events.update();

  if (Minigames.isMinigameActive()) {
    if (buttonB.readButton()) Minigames.primaryAction();
    if (buttonC.readButton())    Minigames.toggleMinigame();
    Minigames.update();
    Minigames.draw();
    return;
  }

  if (buttonC.readButton()) {
    if (menuStack.isOpen()) {
      menuStack.closeAll();
    } else {
      menuStack.push(mainMenu);
    }
  }

  if (menuStack.isOpen()) {
    Display.checkDisplayMenu(Tama, menuStack);

    if (buttonB.readButton())    menuStack.current()->next();
    if (buttonA.readButton()) menuStack.current()->select();
  } else {
    Display.update(Tama, Economy);
    Display.checkDisplayMenu(Tama, menuStack);
  }
}
