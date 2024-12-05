#include "User.h"

User::User(std::string name) : name(name) {}

User::~User() {}

std::string User::getName() const {
    return name;
}
