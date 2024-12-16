#pragma once
#include "Token.h"
#include <unordered_map>
#include <string>

class UserProfile {
public:
    static UserProfile& getInstance();
    
    void updateBalance(const std::string& tokenName, double amount);
    double getTokenBalance(const std::string& tokenName) const;
    double getTotalPortfolioValue() const;
    const std::unordered_map<std::string, double>& getPortfolio() const;
    
private:
    UserProfile() = default;
    std::unordered_map<std::string, double> tokenBalances;
};

