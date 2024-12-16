#pragma once
#include "Market.h"

class FakeDataGenerator {
public:
    static void UpdatePrices();
    static double GenerateRandomPrice(double basePrice);
};

