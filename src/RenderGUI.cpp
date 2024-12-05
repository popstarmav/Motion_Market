#include "RenderGUI.h"
#include "Artist.h"
#include <imgui.h>
#include <iostream>

RenderGUI::RenderGUI() {}

RenderGUI::~RenderGUI() {}

void RenderGUI::renderArtistStats(const Artist& artist) {
    // Use ImGui to display artist stats in the GUI
    if (ImGui::CollapsingHeader(artist.getName().c_str())) {
        ImGui::Text("Views: %d", artist.getViews());
        ImGui::Text("Growth: %.2f%%", artist.getGrowth());
    }
}

void RenderGUI::renderAllArtistsStats(const std::vector<Artist>& artists) {
    ImGui::Begin("Artist Statistics");

    ImGui::Text("Artist Stats Dashboard");
    ImGui::Separator();

    for (const auto& artist : artists) {
        renderArtistStats(artist);
    }

    ImGui::End();
}

