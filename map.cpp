#include "map.h"

Map::Map(int width, int height) : width(width), height(height), mapData(width, std::vector<bool>(height, false)) {}

bool Map::isInside(const Coordinate& coord) const {
    return coord.x >= 0 && coord.x < width && coord.y >= 0 && coord.y < height;
}

bool Map::isOccupied(const Coordinate& coord) const {
    return mapData[coord.x][coord.y];
}

void Map::placeObject(const Coordinate& coord) {
    if (isInside(coord)) {
        mapData[coord.x][coord.y] = true;
    }
}

void Map::removeObject(const Coordinate& coord) {
    if (isInside(coord)) {
        mapData[coord.x][coord.y] = false;
    }
}