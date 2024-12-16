#include "UserProfile.h"
#include "Market.h"

UserProfile& UserProfile::getInstance() {
    static UserProfile instance;
    return instance;
}

void UserProfile::updateBalance(const std::string& tokenName, double amount) {
    tokenBalances[tokenName] += amount;
}

double UserProfile::getTokenBalance(const std::string& tokenName) const {
    auto it = tokenBalances.find(tokenName);
    return (it != tokenBalances.end()) ? it->second : 0.0;
}

double UserProfile::getTotalPortfolioValue() const {
    auto& market = Market::getInstance();
    double total = 0.0;
   
    for (const auto& [token, amount] : tokenBalances) {
        total += amount * market.getLatestPrice(token);
    }
    return total;
}

const std::unordered_map<std::string, double>& UserProfile::getPortfolio() const {
    return tokenBalances;
}


