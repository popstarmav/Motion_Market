#include "FakeDataGenerator.h"
#include <random>
#include <thread>
#include <chrono>

void FakeDataGenerator::UpdatePrices() {
    static auto lastUpdate = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    
    // Update prices every 500ms
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() < 500) {
        return;
    }
    
    lastUpdate = now;
    
    auto& market = Market::getInstance();
    auto& registry = TokenRegistry::getInstance();
    
    for (const auto& tokenName : registry.getAvailableTokens()) {
        auto token = registry.getToken(tokenName);
        if (token) {
            double newPrice = GenerateRandomPrice(token->getCurrentPrice());
            market.updatePrice(tokenName, newPrice);
        }
    }
}

double FakeDataGenerator::GenerateRandomPrice(double basePrice) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // Reduced volatility by lowering the standard deviation
    static std::normal_distribution<> d(0, 0.005);
    
    return basePrice * (1.0 + d(gen));
}
