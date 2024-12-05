#include "Artists.h" // Ensure proper case matches the file name

Artist::Artist(const std::string& name) : name(name), views(0), growth(0) {}

std::string Artist::getName() const {
    return name;
}

int Artist::getViews() const {
    return views;
}

int Artist::getGrowth() const {
    return growth;
}

void Artist::setViews(int views) {
    this->views = views;
}

void Artist::setGrowth(int growth) {
    this->growth = growth;
}

