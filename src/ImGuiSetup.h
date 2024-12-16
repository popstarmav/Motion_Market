#pragma once
#include "Market.h"
#include <GLFW/glfw3.h>
#include <string>

class ImGuiSetup {
public:
    static bool Initialize(const char* windowTitle);
    static void Cleanup();
    static void RenderFrame();
    static bool ShouldClose() { return glfwWindowShouldClose(window); }

private:
    static void RenderMarketView();
    static void RenderTradePanel();
    static void RenderPriceChart();
    static void RenderTransactionHistory();
    static void RenderPortfolio();  // Added portfolio rendering method
    static GLFWwindow* window;
    static std::string selectedToken;
};

