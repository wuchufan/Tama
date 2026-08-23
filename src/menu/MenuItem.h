#pragma once

struct MenuItem {
  const char* label;
  void (*onSelect)(int id);
  int id;
};
