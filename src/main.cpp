#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <unordered_map>
#include <string>

// Mock data structures for demonstration
struct CryptoStock {
    std::string name;
    float price;
    int likes;
    int dislikes;
    int spotifyPlays;
};

struct User {
    std::string name;
    float cash;
    std::unordered_map<std::string, int> portfolio; // Stock name -> number of shares
};

// Function to initialize GLFW error callback
void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

// Function to render the stock market GUI
void RenderStockMarket(std::unordered_map<std::string, CryptoStock>& stocks, User& user) {
    ImGui::Begin("Motion Market");

    ImGui::Text("Welcome to the Motion Market!");
    ImGui::Separator();

    if (ImGui::CollapsingHeader("Market Stocks")) {
        for (auto& [key, stock] : stocks) {
            ImGui::Text("Stock: %s", stock.name.c_str());
            ImGui::Text("Price: $%.2f", stock.price);
            ImGui::Text("Likes: %d | Dislikes: %d", stock.likes, stock.dislikes);
            ImGui::Text("Spotify Plays: %d", stock.spotifyPlays);

            if (ImGui::Button(("Buy " + stock.name).c_str())) {
                if (user.cash >= stock.price) {
                    user.cash -= stock.price;
                    user.portfolio[stock.name]++;
                } else {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Not enough cash!");
                }
            }

            if (ImGui::Button(("Sell " + stock.name).c_str())) {
                if (user.portfolio[stock.name] > 0) {
                    user.cash += stock.price;
                    user.portfolio[stock.name]--;
                } else {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "You don't own this stock!");
                }
            }

            ImGui::Separator();
        }
    }

    if (ImGui::CollapsingHeader("Your Portfolio")) {
        ImGui::Text("Cash: $%.2f", user.cash);
        for (auto& [stockName, shares] : user.portfolio) {
            ImGui::Text("Stock: %s | Shares: %d", stockName.c_str(), shares);
        }
    }

    ImGui::End();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Set GLFW error callback
    glfwSetErrorCallback(glfw_error_callback);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Motion Market - ImGui", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return -1;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Mock data for stocks and user
    std::unordered_map<std::string, CryptoStock> stocks = {
        {"Kendrick Lamar", {"Kendrick Lamar", 200.0f, 1200, 100, 300000}},
        {"Sabrina Carpenter", {"Sabrina Carpenter", 180.0f, 1100, 90, 250000}},
        {"Ariana Grande", {"Ariana Grande", 220.0f, 1300, 120, 400000}},
        {"Taylor Swift", {"Taylor Swift", 300.0f, 2000, 150, 500000}},
        {"Morgan Wallen", {"Morgan Wallen", 170.0f, 900, 80, 180000}},
        {"Cynthia Erivo", {"Cynthia Erivo", 160.0f, 800, 70, 150000}},
        {"Billie Eilish", {"Billie Eilish", 280.0f, 1500, 110, 350000}},
        {"Zach Bryan", {"Zach Bryan", 190.0f, 1000, 85, 220000}},
        {"Jelly Roll", {"Jelly Roll", 140.0f, 700, 60, 140000}},
        {"Tyler, The Creator", {"Tyler, The Creator", 260.0f, 1400, 100, 320000}},
        {"SZA", {"SZA", 230.0f, 1250, 95, 300000}},
        {"Chappell Roan", {"Chappell Roan", 150.0f, 750, 65, 180000}},
        {"Teddy Swims", {"Teddy Swims", 200.0f, 950, 75, 200000}},
        {"Shaboozey", {"Shaboozey", 170.0f, 850, 70, 190000}},
        {"Luke Combs", {"Luke Combs", 240.0f, 1150, 100, 280000}},
        {"Bruno Mars", {"Bruno Mars", 320.0f, 2100, 130, 500000}},
        {"Gracie Abrams", {"Gracie Abrams", 180.0f, 900, 85, 210000}},
        {"Post Malone", {"Post Malone", 290.0f, 1800, 125, 450000}},
        {"The Philly Specials", {"The Philly Specials", 120.0f, 650, 50, 130000}}
    };

    User user = {"Alice", 500.0f, {}};

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start a new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render GUI
        RenderStockMarket(stocks, user);

        // Rendering
        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
