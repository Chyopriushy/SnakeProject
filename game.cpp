#include "game.h"
#include <iostream>
#include <ctime>
#include <locale.h>

Game::Game(int width, int height)
        : map(width, height), snake(Coordinate(width / 2, height / 2)),
          item(FOOD), poison(POISON), isGame(true), direction(0, 1),
          itemTimer(clock()), poisonTimer(clock()) {
    srand(static_cast<unsigned int>(time(nullptr)));
    placeitem();
    placePoison();
    setlocale(LC_ALL, "ko_KR.utf8");
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(FALSE);
}

Game::~Game() {
    endwin();
}

void Game::start() {
    while (isGame) {
        render();
        snakeInput();
        update();
        napms(200);
    }
    renderGameOver();
    askRestart();
}

void Game::placeitem() {
    map.removeObject(item.getCoord());
    item.place(map.getWidth(), map.getHeight(), map);
    map.placeObject(item.getCoord());
    itemTimer = clock();
}

void Game::placePoison() {
    map.removeObject(poison.getCoord());
    poison.place(map.getWidth(), map.getHeight(), map);
    map.placeObject(poison.getCoord());
    poisonTimer = clock();
}

void Game::render() const {
    clear();
    int offsetX = (COLS - map.getWidth()) / 2;
    int offsetY = (LINES - map.getHeight()) / 2;


    for (int y = 0; y < map.getHeight(); ++y) {
        mvprintw(offsetY + y, offsetX, "*");
        mvprintw(offsetY + y, offsetX + map.getWidth() - 1, "*");
    }
    for (int x = 0; x < map.getWidth(); ++x) {
        mvprintw(offsetY, offsetX + x, "*");
        mvprintw(offsetY + map.getHeight() - 1, offsetX + x, "*");
    }


    bool isHead = true;
    for (const auto& part : snake.getBody()) {
        mvprintw(offsetY + part.y, offsetX + part.x, isHead ? "■" : "□");
        isHead = false;
    }


    mvprintw(offsetY + item.getCoord().y, offsetX + item.getCoord().x, "O");
    mvprintw(offsetY + poison.getCoord().y, offsetX + poison.getCoord().x, "X");


    mvprintw(0, COLS - 20, "Score Board");
    mvprintw(1, COLS - 20, "B: %d / %d", snake.getCurrentLength(), snake.getMaxLength());
    mvprintw(2, COLS - 20, "+: %d", snake.getGrowthItems());
    mvprintw(3, COLS - 20, "-: %d", snake.getPoisonItems());
    refresh();
}

void Game::renderGameOver() const {
    clear();
    mvprintw(LINES / 2, (COLS - 10) / 2, "게임오버");
    mvprintw(LINES / 2 + 1, (COLS - 38) / 2, "재시작할거면 Y를 아니면 N을 눌러주세요");
    refresh();
}

void Game::askRestart() {
    nodelay(stdscr, FALSE);
    int ch;
    do {
        ch = getch();
        if (ch == 'y' || ch == 'Y') {
            isGame = true;
            snake = Snake(Coordinate(map.getWidth() / 2, map.getHeight() / 2));
            direction = Coordinate(0, 1);
            placeitem();
            placePoison();
            setlocale(LC_ALL, "");
            nodelay(stdscr, TRUE);
            start();
            return;
        } else if (ch == 'n' || ch == 'N') {
            return;
        }
    } while (true);
}

void Game::update() {
    double poisonTime = (clock() - poisonTimer) / (double) CLOCKS_PER_SEC;
    double itemTime = (clock() - itemTimer) / (double) CLOCKS_PER_SEC;
    if (itemTime >= 0.01) {
        placeitem();
    }
    if (poisonTime >= 0.01) {
        placePoison();
    }

    Coordinate newHead = {snake.getBody().front().x + direction.x, snake.getBody().front().y + direction.y};
    if (!map.isInside(newHead) || newHead.x == 0 || newHead.x == map.getWidth() - 1 || newHead.y == 0 || newHead.y == map.getHeight() - 1 || snake.checkCollision(newHead)) {
        isGame = false;
        return;
    }
    bool add_body = (newHead == item.getCoord());
    if (newHead == poison.getCoord()) {
        snake.reduceBody();
        if (snake.getBody().size() < 3) {
            isGame = false;
            return;
        }
        placePoison();
    } else {
        snake.move(direction, add_body);
        if (add_body) {
            placeitem();
        } else {
            map.removeObject(snake.getBody().back());
        }
    }
    map.placeObject(snake.getBody().front());
}

bool Game::isOppositeDirection(const Coordinate& new_dir) const {
    return (direction.x == -new_dir.x && direction.y == -new_dir.y);
}

void Game::snakeInput() {
    int ch = getch();
    Coordinate new_dir = direction;
    switch (ch) {
        case KEY_UP:
            new_dir = Coordinate(0, -1);
            break;
        case KEY_DOWN:
            new_dir = Coordinate(0, 1);
            break;
        case KEY_LEFT:
            new_dir = Coordinate(-1, 0);
            break;
        case KEY_RIGHT:
            new_dir = Coordinate(1, 0);
            break;
        case 'q':
            isGame = false;
            return;
        default:
            break;
    }

    if (isOppositeDirection(new_dir)) {
        isGame = false;
    } else {
        direction = new_dir;
    }
}