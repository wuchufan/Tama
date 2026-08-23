#include "MenuScreen.h"

MenuScreen::MenuScreen(const MenuItem* itemsIn, int itemCountIn)
  : items(itemsIn), itemCount(itemCountIn), selectedIndex(0) {
}

void MenuScreen::open() {
  selectedIndex = 0;
}

void MenuScreen::next() {
  selectedIndex = (selectedIndex + 1) % itemCount;
}

void MenuScreen::select() {
  
  if (items[selectedIndex].onSelect) { // Check if there is action
    items[selectedIndex].onSelect(items[selectedIndex].id);
  }
}

int MenuScreen::getSelectedIndex() const { return selectedIndex; }
int MenuScreen::getItemCount() const { return itemCount; }
const char* MenuScreen::getLabel(int index) const { return items[index].label; }
