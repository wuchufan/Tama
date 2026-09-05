#pragma once
#include <Arduino.h>

class TamaState {
public:
  int food;
  int happiness;
  int energy;
  int cleanliness;

  TamaState();

  void update();
  void feed();
  void play();
  void sleep();
  void clean();

private:
  int statusDropRate;
};