#include "Market.h"
#include "UserProfile.h"
#include <chrono>

Market& Market::getInstance() {
    static Market instance;
    return instance;
}

void Market::updatePrice(const std::string& tokenName, double price) {
    auto now = std::chrono::system_clock::now().time_since_epoch().count();
    PricePoint point{static_cast<double>(now), price};
    priceHistory[tokenName].push_back(point);
    
    auto token = TokenRegistry::getInstance().getToken(tokenName);
    if (token) {
        token->updatePrice(price);
    }
}

void Market::executeTrade(const std::string& tokenName, double amount, bool isBuy) {
    auto token = TokenRegistry::getInstance().getToken(tokenName);
    if (!token) return;

    // Update user's portfolio
    UserProfile::getInstance().updateBalance(tokenName, isBuy ? amount : -amount);

    TokenTransaction tx{
        isBuy ? "Market" : "User",
        isBuy ? "User" : "Market",
        amount,
        token->getCurrentPrice(),
        static_cast<uint64_t>(std::time(nullptr)),
        "tx_" + std::to_string(std::rand())
    };

    token->addTransaction(tx);
    recentTrades.push_front(tx);
    if (recentTrades.size() > MAX_RECENT_TRADES) {
        recentTrades.pop_back();
    }
}

std::vector<PricePoint> Market::getPriceHistory(const std::string& tokenName) const {
    auto it = priceHistory.find(tokenName);
    return (it != priceHistory.end()) ? it->second : std::vector<PricePoint>{};
}

double Market::getLatestPrice(const std::string& tokenName) const {
    auto it = priceHistory.find(tokenName);
    if (it != priceHistory.end() && !it->second.empty()) {
        return it->second.back().price;
    }
    return 0.0;
}

const std::deque<TokenTransaction>& Market::getRecentTrades() const {
    return recentTrades;
}

