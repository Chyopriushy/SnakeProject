#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
    int x, y;
    Coordinate(int x = 0, int y = 0);
    bool operator==(const Coordinate& other) const;
    bool operator!=(const Coordinate& other) const;
};

#endif // COORDINATE_H
