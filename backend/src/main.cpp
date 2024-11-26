#include "crypto_api.h"
#include "spotify_api.h"
#include "utils.h"
#include <iostream>
#include <string>

int main() {
    std::string crypto, artist, project;
    double investment;

    std::cout << "Enter the cryptocurrency you want to invest in (e.g., BTC, ETH, DOGE): ";
    std::cin >> crypto;

    std::cout << "Enter the amount you want to invest (in USD): ";
    std::cin >> investment;

    double cryptoPrice = getCryptoPrice(crypto);
    if (cryptoPrice <= 0) {
        std::cerr << "Failed to fetch cryptocurrency price.\n";
        return 1;
    }

    std::cout << "Enter the artist you want to invest in: ";
    std::cin.ignore(); // Clear buffer
    std::getline(std::cin, artist);

    std::cout << "Is this for a project (e.g., album, EP)? If yes, enter the project name: ";
    std::getline(std::cin, project);

    double investmentValue = calculateInvestmentValue(investment, cryptoPrice);
    std::cout << "\nInvestment Results:\n";
    std::cout << "Cryptocurrency: " << crypto << "\n";
    std::cout << "Artist: " << artist << "\n";
    if (!project.empty()) {
        std::cout << "Project: " << project << "\n";
    }
    std::cout << "Your Investment Value: $" << investmentValue << "\n";

    return 0;
}
