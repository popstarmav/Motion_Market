#include "Market.h"
#include "User.h"
#include "RenderGUI.h"
#include <iostream>
#include <cstdlib>

Market::Market() {
    // Add artist names to the list
    artists.push_back(Artist("Kendrick Lamar"));
    artists.push_back(Artist("Sabrina Carpenter"));
    artists.push_back(Artist("Ariana Grande"));
    artists.push_back(Artist("Taylor Swift"));
    artists.push_back(Artist("Morgan Wallen"));
    artists.push_back(Artist("Cynthia Erivo"));
    artists.push_back(Artist("Billie Eilish"));
    artists.push_back(Artist("Zach Bryan"));
    artists.push_back(Artist("Jelly Roll"));
    artists.push_back(Artist("Tyler, The Creator"));
    artists.push_back(Artist("SZA"));
    artists.push_back(Artist("Chappell Roan"));
    artists.push_back(Artist("Teddy Swims"));
    artists.push_back(Artist("Shaboozey"));
    artists.push_back(Artist("Luke Combs"));
    artists.push_back(Artist("Bruno Mars"));
    artists.push_back(Artist("Gracie Abrams"));
    artists.push_back(Artist("Post Malone"));
    artists.push_back(Artist("The Philly Specials"));
}

Market::~Market() {
    // Clean up if necessary
}

void Market::generateStats() {
    // Generate fake stats (for views, growth, etc.) and OHLC data
    for (auto& artist : artists) {
        artist.setViews(rand() % 1000000);  // Random views for each artist
        artist.setGrowth(rand() % 1000);   // Random growth for each artist

        // Generate OHLC data for the artist's stock
        CryptoStock stock;
        stock.name = artist.getName();
        stock.price = 100.0f + (rand() % 500) / 10.0f;  // Random base price
        for (int i = 0; i < 30; ++i) {  // Generate 30 days of historical data
            GenerateOHLC(stock);
        }
        stocks[artist.getName()] = stock;
    }
}

void Market::renderStats(RenderGUI& renderGUI) {
    // Loop through artists and render their stats and candlestick charts in the GUI
    for (auto& artist : artists) {
        renderGUI.renderArtistStats(artist);

        // Render candlestick chart for the artist's stock
        auto it = stocks.find(artist.getName());
        if (it != stocks.end()) {
            renderGUI.renderCandlestickChart(it->second);
        }
    }
}

