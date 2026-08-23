#include "MenuStack.h"

MenuStack::MenuStack() : depth(0) {
}

void MenuStack::push(MenuScreen& screen) {
  if (depth >= MAX_DEPTH) return;
  screen.open();
  screens[depth] = &screen;
  depth++;
}

void MenuStack::pop() {
  if (depth > 0) depth--;
}

void MenuStack::closeAll() {
  depth = 0;
}

bool MenuStack::isOpen() const {
  return depth > 0;
}

MenuScreen* MenuStack::current() {
  return depth > 0 ? screens[depth - 1] : nullptr;
}
