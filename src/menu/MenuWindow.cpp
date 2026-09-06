#include "MenuWindow.h"

MenuWindow::MenuWindow(const MenuItem* itemsIn, int itemCountIn)
  : items(itemsIn), itemCount(itemCountIn), selectedIndex(0) {
}

void MenuWindow::open() {
  selectedIndex = 0;
}

void MenuWindow::next() {
  selectedIndex = (selectedIndex + 1) % itemCount;
}

void MenuWindow::select() {

  if (items[selectedIndex].onSelect) { // Check if there is action
    items[selectedIndex].onSelect(items[selectedIndex].id);
  }
}

int MenuWindow::getSelectedIndex() const { return selectedIndex; }
int MenuWindow::getItemCount() const { return itemCount; }
const char* MenuWindow::getLabel(int index) const { return items[index].label; }
