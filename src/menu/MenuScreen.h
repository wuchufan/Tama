#pragma once
#include "MenuItem.h"

class MenuScreen {
public:
  MenuScreen(const MenuItem* items, int itemCount);

  void open();   // resets selection, called when this screen becomes active
  void next();
  void select(); // invokes the current item's onSelect callback

  int getSelectedIndex() const;
  int getItemCount() const;
  const char* getLabel(int index) const;

private:
  const MenuItem* items;
  int itemCount;
  int selectedIndex;
};
