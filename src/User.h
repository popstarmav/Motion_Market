#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(std::string name);
    ~User();

    std::string getName() const;

private:
    std::string name;
};

#endif // USER_H
