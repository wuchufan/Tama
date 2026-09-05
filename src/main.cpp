#include "InputManager.h"
#include "TamaState.h"
#include "display/DisplayManager.h"
#include "CharacterManager.h"
#include "TamaEventsManager.h"
#include "EconomyManager.h"
#include "minigames/MinigameManager.h"
#include "menu/MenuActions.h"

InputManager buttonConfirm(1);
InputManager buttonNext(2);
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

  buttonConfirm.init();
  buttonNext.init();
  buttonC.init();
}

void loop() {
  Tama.update();
  Character.update();
  Events.update();

  if (Minigames.isMinigameActive()) {
    if (buttonNext.readButton()) Minigames.primaryAction();
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

    if (buttonNext.readButton())    menuStack.current()->next();
    if (buttonConfirm.readButton()) menuStack.current()->select();
  } else {
    Display.update(Tama);
    Display.checkDisplayMenu(Tama, menuStack);
  }
}
