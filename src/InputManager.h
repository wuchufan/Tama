#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <cstdint>
#include <Arduino.h>


class InputManager {
private:
    uint32_t buttonPin;
    uint32_t lastDebounceTime;
    const uint32_t debounceDelay;


public:
    InputManager(uint8_t pin);
    bool lastButtonState;
    bool buttonState;

    void init();
    bool readButton();
    bool isLeftPressed();
    bool isOkPressed();
    bool isRightPressed();
};

#endif