//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_GAME_H
#define MAIN_C_GAME_H

#include "../rendering.h"
#include "snake.h"

#define CELL_SIZE 10

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum WindowState StartGame(GameRenderer *renderer);

#endif //MAIN_C_GAME_H
