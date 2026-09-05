#include "EconomyManager.h"
#include "Config.h"

EconomyManager::EconomyManager() : money(Config::Economy::INITIAL_MONEY) {
  for (int i = 0; i < ITEM_COUNT; i++) quantities[i] = initialQuantityOf(static_cast<ShopItem>(i));
}

int EconomyManager::getMoney() const {
  return money;
}

void EconomyManager::earn(int amount) {
  money += amount;
}

bool EconomyManager::spend(int amount) {
  if (money < amount) return false;
  money -= amount;
  return true;
}

int EconomyManager::priceOf(ShopItem item) const {
  return Config::Shop::ITEMS[static_cast<int>(item)].price;
}

int EconomyManager::initialQuantityOf(ShopItem item) const {
  return Config::Shop::ITEMS[static_cast<int>(item)].initialQuantity;
}

bool EconomyManager::purchase(ShopItem item) {
  if (!spend(priceOf(item))) return false;
  quantities[static_cast<int>(item)]++;
  return true;
}

int EconomyManager::getQuantity(ShopItem item) const {
  return quantities[static_cast<int>(item)];
}
