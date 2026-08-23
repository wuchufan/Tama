#pragma once
#include "MenuScreen.h"

class MenuStack {
public:
  MenuStack();

  void push(MenuScreen& screen);
  void pop();
  void closeAll();

  bool isOpen() const;
  MenuScreen* current();

private:
  static const int MAX_DEPTH = 4;
  MenuScreen* screens[MAX_DEPTH];

  int depth;
};
