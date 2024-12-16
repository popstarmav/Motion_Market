#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

struct TokenMetadata {
    std::string artistName;
    std::string description;
    std::string imageUrl;
    uint64_t totalSupply;
    uint64_t circulatingSupply;
};

struct TokenTransaction {
    std::string fromAddress;
    std::string toAddress;
    double amount;
    double price;
    uint64_t timestamp;
    std::string txHash;
};

class Token {
public:
    Token(const std::string& name, uint64_t initialSupply);
    
    const TokenMetadata& getMetadata() const { return metadata; }
    double getCurrentPrice() const { return currentPrice; }
    const std::vector<TokenTransaction>& getTransactionHistory() const { return transactions; }
    
    bool transfer(const std::string& from, const std::string& to, double amount);
    void updatePrice(double newPrice);
    void addTransaction(const TokenTransaction& tx);

private:
    TokenMetadata metadata;
    double currentPrice;
    std::vector<TokenTransaction> transactions;
};

class TokenRegistry {
public:
    static TokenRegistry& getInstance();
    
    std::shared_ptr<Token> createToken(const std::string& artistName, uint64_t initialSupply);
    std::shared_ptr<Token> getToken(const std::string& artistName);
    std::vector<std::string> getAvailableTokens() const;

private:
    TokenRegistry() = default;
    std::unordered_map<std::string, std::shared_ptr<Token>> tokens;
};

