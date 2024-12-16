#include "ImGuiSetup.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "UserProfile.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

GLFWwindow* ImGuiSetup::window = nullptr;
std::string ImGuiSetup::selectedToken;

bool ImGuiSetup::Initialize(const char* windowTitle) {
    if (!glfwInit())
        return false;

    window = glfwCreateWindow(1280, 720, windowTitle, NULL, NULL);
    if (!window)
        return false;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
   
    ImGui::StyleColorsDark();
    ImPlot::StyleColorsDark();
   
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
   
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

void ImGuiSetup::RenderFrame() {
    glfwPollEvents();
   
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderMarketView();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void ImGuiSetup::RenderMarketView() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Music Token Market", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse);
   
    auto tokens = TokenRegistry::getInstance().getAvailableTokens();
    if (ImGui::BeginCombo("Select Artist Token", selectedToken.c_str())) {
        for (const auto& token : tokens) {
            if (ImGui::Selectable(token.c_str(), token == selectedToken)) {
                selectedToken = token;
            }
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();
    auto& market = Market::getInstance();
    double currentPrice = market.getLatestPrice(selectedToken);
    ImGui::Text("Current Price: $%.2f", currentPrice);

    ImGui::Columns(2, "MainColumns", false);
    
    RenderPriceChart();
    RenderPortfolio();
    
    ImGui::NextColumn();
    RenderTradePanel();
    RenderTransactionHistory();
    
    ImGui::Columns(1);
    ImGui::End();
}

void ImGuiSetup::RenderPriceChart() {
    ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(10, 10));
    
    if (ImPlot::BeginPlot("##PriceChart", ImVec2(-1, 400))) {
        ImPlot::SetupAxis(ImAxis_X1, "Time");
        ImPlot::SetupAxis(ImAxis_Y1, "Price ($)");
        
        auto& market = Market::getInstance();
        auto history = market.getPriceHistory(selectedToken);
        
        std::vector<double> times, prices;
        for (const auto& point : history) {
            times.push_back(point.time);
            prices.push_back(point.price);
        }
        
        if (!times.empty()) {
            ImPlot::PlotLine("Token Price", times.data(), prices.data(), times.size());
            
            if (prices.size() > 1) {
                auto [min_it, max_it] = std::minmax_element(prices.begin(), prices.end());
                size_t min_idx = std::distance(prices.begin(), min_it);
                size_t max_idx = std::distance(prices.begin(), max_it);
                
                ImPlot::Annotation(times[min_idx], *min_it, 
                    ImVec4(1,0,0,1), ImVec2(0,10), true, "Min: $%.2f", *min_it);
                ImPlot::Annotation(times[max_idx], *max_it, 
                    ImVec4(0,1,0,1), ImVec2(0,-10), true, "Max: $%.2f", *max_it);
            }
        }
        
        ImPlot::EndPlot();
    }
    ImPlot::PopStyleVar();
}

void ImGuiSetup::RenderPortfolio() {
    ImGui::BeginChild("Portfolio", ImVec2(0, 200), true);
    ImGui::Text("Your Portfolio");
    ImGui::Separator();
   
    auto& profile = UserProfile::getInstance();
    auto& market = Market::getInstance();
   
    if (ImGui::BeginTable("Holdings", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Artist Token");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableSetupColumn("Current Price");
        ImGui::TableSetupColumn("Total Value");
        ImGui::TableHeadersRow();
       
        for (const auto& [token, amount] : profile.getPortfolio()) {
            if (amount > 0) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", token.c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%.2f", amount);
                double price = market.getLatestPrice(token);
                ImGui::TableNextColumn();
                ImGui::Text("$%.2f", price);
                ImGui::TableNextColumn();
                ImGui::Text("$%.2f", amount * price);
            }
        }
        ImGui::EndTable();
    }
   
    ImGui::Text("Total Portfolio Value: $%.2f", profile.getTotalPortfolioValue());
    ImGui::EndChild();
}

void ImGuiSetup::RenderTradePanel() {
    ImGui::BeginChild("Trade Panel", ImVec2(0, 120), true);
    
    static float amount = 1.0f;
    ImGui::InputFloat("Amount", &amount, 0.1f, 1.0f, "%.1f tokens");
    
    auto& market = Market::getInstance();
    double currentPrice = market.getLatestPrice(selectedToken);
    ImGui::Text("Total Cost: $%.2f", currentPrice * amount);
    
    ImGui::Spacing();
    
    if (ImGui::Button("Buy", ImVec2(120, 40))) {
        market.executeTrade(selectedToken, amount, true);
    }
    ImGui::SameLine();
    if (ImGui::Button("Sell", ImVec2(120, 40))) {
        market.executeTrade(selectedToken, amount, false);
    }
    
    ImGui::EndChild();
}

void ImGuiSetup::RenderTransactionHistory() {
    ImGui::BeginChild("Transaction History", ImVec2(0, 200), true);
    ImGui::Text("Recent Transactions");
    ImGui::Separator();
    
    auto& market = Market::getInstance();
    const auto& trades = market.getRecentTrades();
    
    if (ImGui::BeginTable("Trades", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Time");
        ImGui::TableSetupColumn("Type");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableSetupColumn("Price");
        ImGui::TableHeadersRow();
        
        for (const auto& tx : trades) {
            ImGui::TableNextRow();
            
            std::time_t t = tx.timestamp;
            std::tm* ltm = std::localtime(&t);
            char timeStr[32];
            std::strftime(timeStr, sizeof(timeStr), "%H:%M:%S", ltm);
            
            ImGui::TableNextColumn();
            ImGui::Text("%s", timeStr);
            
            ImGui::TableNextColumn();
            bool isBuy = tx.toAddress == "User";
            ImGui::TextColored(isBuy ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1), 
                             isBuy ? "BUY" : "SELL");
            
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", tx.amount);
            
            ImGui::TableNextColumn();
            ImGui::Text("$%.2f", tx.price);
        }
        ImGui::EndTable();
    }
    
    ImGui::EndChild();
}

void ImGuiSetup::Cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
