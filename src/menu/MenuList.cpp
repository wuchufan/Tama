#include "MenuList.h"

void MenuList::draw(MenuWindow& screen, TFT_eSprite& canvas) {
  canvas.fillSprite(TFT_BLACK);

  int itemCount = screen.getItemCount();
  int selectedIndex = screen.getSelectedIndex();

  const int marginX = 10;
  const int marginY = 10;
  const int gap = 6;
  const int selectedBump = 6;
  const int bubbleWidth = 240 - 2 * marginX;

  int availableHeight = 240 - 2 * marginY;
  int bubbleHeight = (availableHeight - (itemCount - 1) * gap) / itemCount;

  canvas.setTextSize(2);

  for (int i = 0; i < itemCount; i++) {
    int cellY = marginY + i * (bubbleHeight + gap);
    bool selected = (i == selectedIndex);

    int w = bubbleWidth + (selected ? selectedBump : 0);
    int h = bubbleHeight + (selected ? selectedBump : 0);
    int x = marginX - (selected ? selectedBump / 2 : 0);
    int y = cellY - (selected ? selectedBump / 2 : 0);

    if (selected) {
      canvas.fillRoundRect(x, y, w, h, h / 2, TFT_YELLOW);
      canvas.setTextColor(TFT_BLACK, TFT_YELLOW);
    } else {
      canvas.drawRoundRect(x, y, w, h, h / 2, TFT_WHITE);
      canvas.setTextColor(TFT_WHITE, TFT_BLACK);
    }

    const char* label = screen.getLabel(i);
    int textW = canvas.textWidth(label);
    int textX = x + (w - textW) / 2;
    int textY = y + (h - 16) / 2; // text size 2 glyph height ~16px
    canvas.setCursor(textX, textY);
    canvas.print(label);
  }
}
