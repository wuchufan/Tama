#include "MenuGrid.h"

MenuGrid::MenuGrid(TFT_eSPI& tftRef) : tft(tftRef) {
}

void MenuGrid::draw(MenuScreen& screen) {
  tft.fillScreen(TFT_BLACK);

  const int cols = 3;
  const int rows = 3;
  const int margin = 10;
  const int gap = 10;
  const int cellW = (240 - 2 * margin - (cols - 1) * gap) / cols;
  const int cellH = (240 - 2 * margin - (rows - 1) * gap) / rows;
  const int padding = 8;
  const int selectedBump = 8;

  const uint16_t palette[9] = { TFT_RED, TFT_ORANGE, TFT_YELLOW, TFT_GREEN, TFT_CYAN, TFT_BLUE, TFT_MAGENTA, TFT_WHITE, TFT_PINK };

  int slotCount = cols * rows;
  for (int i = 0; i < slotCount && i < screen.getItemCount(); i++) {
    int col = i % cols;
    int row = i / cols;
    int cellX = margin + col * (cellW + gap);
    int cellY = margin + row * (cellH + gap);

    bool selected = (i == screen.getSelectedIndex());
    int iconW = cellW - 2 * padding + (selected ? selectedBump : 0);
    int iconH = cellH - 2 * padding + (selected ? selectedBump : 0);
    int iconX = cellX + (cellW - iconW) / 2;
    int iconY = cellY + (cellH - iconH) / 2;

    tft.fillRoundRect(iconX, iconY, iconW, iconH, 6, palette[i % 9]);
  }
}
