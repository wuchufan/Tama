#pragma once

namespace Config {
  namespace Tama {
    constexpr int INITIAL_FOOD = 100;
    constexpr int INITIAL_HAPPINESS = 100;
    constexpr int INITIAL_ENERGY = 100;
    constexpr int STATUS_DROP_RATE = 1000; // ms between stat decay ticks
  }

  namespace Events {
    constexpr unsigned long CHECK_INTERVAL = 10000; // check every 10s (placeholder)
    constexpr int CHANCE_PERCENT = 20;               // % chance per check (placeholder)
    constexpr unsigned long SICK_DURATION = 30000;   // auto-recovers if not cured (placeholder)
  }

  namespace Growth {
    constexpr unsigned long EGG_DURATION = 3000;     // placeholder
    constexpr unsigned long INFANCY_DURATION = 3000; // placeholder
    constexpr unsigned long PUBERTY_DURATION = 3000; // placeholder
  }

  namespace Economy {
    constexpr int INITIAL_MONEY = 1000000;
  }

  namespace Shop {
    struct ItemInfo {
      int price;
      int initialQuantity;
    };

    // indexed by ShopItem — row order must match the enum's declaration order
    constexpr ItemInfo ITEMS[] = {
      { 200, 0 }, // PLAYSTATION
      { 15,  0 }, // SHEPHERDS_PIE
      { 5,   0 }, // CHIPS
      { 3,   0 }, // DIET_COKE
    };
  }
}
