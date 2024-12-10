#include "RenderGUI.h"
#include <GLFW/glfw3.h>
#include <implot.h>
#include <tuple>
#include <vector>
#include <iostream>

// Implementation of run
void RenderGUI::run(const std::vector<std::tuple<float, float, float, float>>& data) {
    // Initialize ImGui and ImPlot
    if (!glfwInit()) return;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Candlestick Graph", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    ImGui::CreateContext();
    ImPlot::CreateContext();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui::NewFrame();
        if (ImPlot::BeginPlot("Candlestick Chart")) {
            // Extract data into arrays for rendering
            std::vector<float> opens, highs, lows, closes;
            for (const auto& [open, high, low, close] : data) {
                opens.push_back(open);
                highs.push_back(high);
                lows.push_back(low);
                closes.push_back(close);
            }

            // Render candlesticks manually
            for (size_t i = 0; i < opens.size(); ++i) {
                float x = static_cast<float>(i); // X-axis value (index)
                float open = opens[i];
                float close = closes[i];
                float high = highs[i];
                float low = lows[i];

                // Set the color for bullish (green) or bearish (red)
                if (close > open) {
                    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green
                } else {
                    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
                }

                // Draw the high-low line
                float highLowX[2] = {x, x};
                float highLowY[2] = {low, high};
                ImPlot::PlotLine("##HighLow", highLowX, highLowY, 2);

                // Draw the open-close rectangle (as a line for simplicity)
                float openCloseX[2] = {x - 0.2f, x + 0.2f};
                float openCloseY[2] = {open, close};
                ImPlot::PlotLine("##OpenClose", openCloseX, openCloseY, 2);

                ImPlot::PopStyleColor(); // Restore color
            }

            ImPlot::EndPlot();
        }

        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Implementation of renderArtistStats
void RenderGUI::renderArtistStats(const Artist& artist) {
    // Example implementation
    std::cout << "Rendering artist stats for: " << artist.getName() << std::endl;
    // Add ImGui/ImPlot code here if required
}

// Implementation of renderStockPriceChart
void RenderGUI::renderStockPriceChart(const std::string& artistName, float stockPrice) {
    // Example implementation
    std::cout << "Rendering stock price chart for " << artistName 
              << " with price: " << stockPrice << std::endl;
    // Add ImGui/ImPlot code here if required
}


