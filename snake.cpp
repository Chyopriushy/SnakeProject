#include "snake.h"

Snake::Snake(const Coordinate& start, int initialLength)
        : direction(0, 1), growthItemCount(0), poisonItemCount(0), maxLength(initialLength) {
    for (int i = 0; i < initialLength; ++i) {
        body.push_back(Coordinate(start.x - i, start.y));
    }
}

void Snake::move(const Coordinate& new_dir, bool add_body) {
    Coordinate newHead = {body.front().x + new_dir.x, body.front().y + new_dir.y};
    body.push_front(newHead);
    if (!add_body) {
        body.pop_back();
    }else {
        maxLength = std::max(maxLength, static_cast<int>(body.size()));
    }
    if (add_body) growthItemCount++;
}

bool Snake::checkCollision(const Coordinate& newHead) const {
    for (const auto& part : body) {
        if (part == newHead) {
            return true;
        }
    }
    return false;
}

const std::deque<Coordinate>& Snake::getBody() const {
    return body;
}

Coordinate Snake::getDir() const {
    return direction;
}

void Snake::reduceBody() {
    if (body.size() > 1) {
        body.pop_back();
        poisonItemCount++;
    }
}