#ifndef MARKET_H
#define MARKET_H

#include "User.h"
#include "RenderGUI.h"
#include <vector>
#include <string>

class Market {
public:
    Market();
    ~Market();

    void generateStats(); // Will generate stats for artists
    void renderStats(RenderGUI& renderGUI); // Pass RenderGUI to update display

private:
    std::vector<Artist> artists;
    // Add other data members as needed
};

#endif // MARKET_H
