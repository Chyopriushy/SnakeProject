#ifndef MAP_H
#define MAP_H

#include <vector>
#include "coordinate.h"

class Map {
public:
    Map(int width, int height);
    bool isInside(const Coordinate& coord) const;
    bool isOccupied(const Coordinate& coord) const;
    void placeObject(const Coordinate& coord);
    void removeObject(const Coordinate& coord);
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width, height;
    std::vector<std::vector<bool>> mapData;
};

#endif // MAP_H