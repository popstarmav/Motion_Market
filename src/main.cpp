#include "ImGuiSetup.h"
#include "Market.h"
#include "FakeDataGenerator.h"

int main() {
    if (!ImGuiSetup::Initialize("Music Token Market")) {
        return -1;
    }

    auto& registry = TokenRegistry::getInstance();
    registry.createToken("Taylor Swift", 1000000);
    registry.createToken("Drake", 1000000);
    registry.createToken("BTS", 1000000);
    registry.createToken("The Weeknd", 1000000);
    registry.createToken("Bad Bunny", 1000000);

    while (!ImGuiSetup::ShouldClose()) {
        ImGuiSetup::RenderFrame();
        FakeDataGenerator::UpdatePrices();
    }

    ImGuiSetup::Cleanup();
    return 0;
}

