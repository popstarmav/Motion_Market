#include "artists.h"
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding randomness

// Initialize random seed
void initRandomSeed() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(0));
        seeded = true;
    }
}

// Generate a list of mock artists
std::vector<Artist> generateMockArtists() {
    initRandomSeed();

    return {
        {"Taylor Swift", rand() % 2000000 + 1000000, rand() % 2000000 + 1500000, 120.50 + (rand() % 100 - 50) * 0.1},
        {"Drake", rand() % 1000000 + 500000, rand() % 1500000 + 800000, 95.75 + (rand() % 80 - 40) * 0.1},
        {"Beyoncé", rand() % 2000000 + 1000000, rand() % 2500000 + 1200000, 135.00 + (rand() % 120 - 60) * 0.1},
        {"Adele", rand() % 1800000 + 800000, rand() % 2200000 + 1000000, 110.25 + (rand() % 90 - 45) * 0.1},
        {"Ed Sheeran", rand() % 1500000 + 700000, rand() % 2000000 + 900000, 102.30 + (rand() % 70 - 35) * 0.1}
    };
}

// Update stock prices for all artists based on mock algorithm
void updateStockPrices(std::vector<Artist>& artists) {
    for (auto& artist : artists) {
        double random_change = (rand() % 20 - 10) * 0.1;  // Random change between -1.0 and +1.0
        artist.stock_price += random_change;

        // Ensure stock price doesn't fall below $1.00
        if (artist.stock_price < 1.0) {
            artist.stock_price = 1.0;
        }
    }
}
