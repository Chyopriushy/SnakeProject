#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "snake.h"
#include "item.h"
#include <ncurses.h>
#include <ctime>

class Game {
public:
    Game(int width, int height);
    ~Game();
    void start();

private:
    void placeitem();
    void placePoison();
    void render() const;
    void update();
    void snakeInput();
    void renderGameOver() const;
    void askRestart();
    bool isOppositeDirection(const Coordinate& new_dir) const;


    Map map;
    Snake snake;
    Item item;
    Item poison;
    bool isGame;
    Coordinate direction;
    clock_t itemTimer;
    clock_t poisonTimer;

};

#endif // GAME_H