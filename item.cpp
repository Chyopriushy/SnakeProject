#include "item.h"
#include <cstdlib>

Item::Item(Item_type type) : type(type) {}

void Item::place(int width, int height, const Map& map) {
    int x = rand() % (width - 2) + 1;
    int y = rand() % (height - 2) + 1;
    position = Coordinate(x, y);
    do {
        x = rand() % (width - 2) + 1;
        y = rand() % (height - 2) + 1;
        position = Coordinate(x, y);
    } while (map.isOccupied(position));
}

Coordinate Item::getCoord() const {
    return position;
}

Item_type Item::getType() const {
    return type;
}