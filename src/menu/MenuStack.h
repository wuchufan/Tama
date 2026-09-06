#pragma once
#include "MenuWindow.h"

class MenuStack {
public:
  MenuStack();

  void push(MenuWindow& screen);
  void pop();
  void closeAll();

  int getDepth() const;
  MenuWindow* current();

private:
  static const int MAX_DEPTH = 4;
  MenuWindow* screens[MAX_DEPTH];

  int depth;
};
