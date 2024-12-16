#pragma once
#include "Token.h"
#include <vector>
#include <deque>

struct PricePoint {
    double time;
    double price;
};

class Market {
public:
    static Market& getInstance();
    void updatePrice(const std::string& tokenName, double price);
    void executeTrade(const std::string& tokenName, double amount, bool isBuy);
    
    std::vector<PricePoint> getPriceHistory(const std::string& tokenName) const;
    double getLatestPrice(const std::string& tokenName) const;
    const std::deque<TokenTransaction>& getRecentTrades() const;

private:
    Market() = default;
    std::unordered_map<std::string, std::vector<PricePoint>> priceHistory;
    std::deque<TokenTransaction> recentTrades;
    static constexpr size_t MAX_RECENT_TRADES = 100;
};

