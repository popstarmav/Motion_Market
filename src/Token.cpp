#include "Token.h"
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

Token::Token(const std::string& name, uint64_t initialSupply) {
    metadata.artistName = name;
    metadata.totalSupply = initialSupply;
    metadata.circulatingSupply = initialSupply;
    currentPrice = 100.0;
}

bool Token::transfer(const std::string& from, const std::string& to, double amount) {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()).count();

    std::stringstream ss;
    ss << std::hex << timestamp << from << to << amount;
    std::string txHash = ss.str();

    TokenTransaction tx{
        from,
        to,
        amount,
        currentPrice,
        static_cast<uint64_t>(timestamp),
        txHash
    };

    transactions.push_back(tx);
    return true;
}

void Token::updatePrice(double newPrice) {
    currentPrice = newPrice;
}

void Token::addTransaction(const TokenTransaction& tx) {
    transactions.push_back(tx);
}

TokenRegistry& TokenRegistry::getInstance() {
    static TokenRegistry instance;
    return instance;
}

std::shared_ptr<Token> TokenRegistry::createToken(const std::string& artistName, uint64_t initialSupply) {
    auto token = std::make_shared<Token>(artistName, initialSupply);
    tokens[artistName] = token;
    return token;
}

std::shared_ptr<Token> TokenRegistry::getToken(const std::string& artistName) {
    auto it = tokens.find(artistName);
    return (it != tokens.end()) ? it->second : nullptr;
}

std::vector<std::string> TokenRegistry::getAvailableTokens() const {
    std::vector<std::string> tokenList;
    for (const auto& pair : tokens) {
        tokenList.push_back(pair.first);
    }
    return tokenList;
}

