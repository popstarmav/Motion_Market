#ifndef RENDER_GUI_H
#define RENDER_GUI_H

#include <tuple>
#include "Artists.h"
#include <vector>

class RenderGUI {
public:
    void renderArtistStats(const Artist& artist);
    void renderStockPriceChart(const std::string& artistName, float stockPrice);
    void run(const std::vector<std::tuple<float, float, float, float>>& data);
};

#endif
 // RENDER_GUI_H