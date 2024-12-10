#ifndef MARKET_H
#define MARKET_H

#include "User.h"
#include "Artists.h"
#include "RenderGUI.h"
#include <vector>
#include <map>    // For stock price storage
#include <string> // For artist names

class Market {
public:
    Market();
    ~Market();

    void generateStats(); // Generate stats for artists
    void renderStats(RenderGUI& renderGUI); // Pass RenderGUI to update display

private:
    std::vector<Artist> artists;             // List of artists
    std::map<std::string, float> artistStocks; // Map of artist names to stock prices
};

#endif // MARKET_H

