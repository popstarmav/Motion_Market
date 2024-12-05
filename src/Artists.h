#ifndef ARTIST_H
#define ARTIST_H

#include <string>

class Artist {
public:
    Artist(const std::string& name);

    std::string getName() const;
    int getViews() const;
    int getGrowth() const;

    void setViews(int views);
    void setGrowth(int growth);

private:
    std::string name;
    int views;
    int growth;
};

#endif // ARTIST_H
 // ARTISTS_H
