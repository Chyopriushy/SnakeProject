#ifndef ITEM_H
#define ITEM_H

#include "coordinate.h"
#include "map.h"

enum Item_type { FOOD, POISON };

class Item {
public:
    Item(Item_type type);
    void place(int width, int height, const Map& map);
    Coordinate getCoord() const;
    Item_type getType() const;

private:
    Coordinate position;
    Item_type type;
};

#endif // ITEM_H
