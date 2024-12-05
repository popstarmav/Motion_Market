#ifndef RENDERGUI_H
#define RENDERGUI_H

#include "Artist.h"
#include <string>

class RenderGUI {
public:
    RenderGUI();
    ~RenderGUI();

    void renderArtistStats(const Artist& artist);  // Render stats for a specific artist
    void renderAllArtistsStats(const std::vector<Artist>& artists); // Render all artists' stats
};

#endif // RENDERGUI_H
