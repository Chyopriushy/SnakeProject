#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "coordinate.h"

class Snake {
public:
    Snake(const Coordinate& start, int initialLength = 3);
    void move(const Coordinate& direction, bool add_body);
    bool checkCollision(const Coordinate& newHead) const;
    const std::deque<Coordinate>& getBody() const;
    Coordinate getDir() const;
    void reduceBody();
    int getGrowthItems() const { return growthItemCount; }
    int getPoisonItems() const { return poisonItemCount; }
    int getCurrentLength() const { return body.size(); }
    int getMaxLength() const { return maxLength; }
private:
    std::deque<Coordinate> body;
    Coordinate direction;
    int growthItemCount;
    int poisonItemCount;
    int maxLength;
};

#endif // SNAKE_H