#pragma once

enum class ShopItem {
  PLAYSTATION,
  SHEPHERDS_PIE,
  CHIPS,
  DIET_COKE,
  COUNT // sentinel, always keep last; not a real item
};

class EconomyManager {
public:
  EconomyManager();

  int getMoney() const;
  void earn(int amount);
  bool spend(int amount); // false if insufficient funds; balance unchanged in that case

  bool purchase(ShopItem item); // spends the item's configured price; false if insufficient funds
  int getQuantity(ShopItem item) const;

private:
  static const int ITEM_COUNT = static_cast<int>(ShopItem::COUNT);

  int money;
  int quantities[ITEM_COUNT];

  int priceOf(ShopItem item) const;
  int initialQuantityOf(ShopItem item) const;
};
