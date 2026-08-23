#include "inputManager.h"

InputManager::InputManager(uint8_t pin)
:lastDebounceTime(0),
 debounceDelay(30),
 buttonPin(pin),
 lastButtonState(HIGH),
 buttonState(HIGH)
{}

void InputManager::init(){
  pinMode(buttonPin, INPUT_PULLUP);
}


bool InputManager::readButton(){

    // return false;
    bool reading = digitalRead(buttonPin);

    // Reset debounce timer when reading changes
    if (reading != lastButtonState && ((millis() - lastDebounceTime) > debounceDelay)) {
        lastDebounceTime = millis();
    }

    // Check if the signal is stable
    if ((millis() - lastDebounceTime) > debounceDelay) {

        // Button state changed
        if (reading != buttonState) {

            buttonState = reading;

            // Trigger only on press
            if (buttonState == LOW) {
                return true;
            }
        }
    }
    lastButtonState = reading;
    return false;
}

