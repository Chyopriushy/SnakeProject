#include "coordinate.h"

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

bool Coordinate::operator==(const Coordinate& other) const {
    return x == other.x && y == other.y;
}

bool Coordinate::operator!=(const Coordinate& other) const {
    return !(*this == other);
}
