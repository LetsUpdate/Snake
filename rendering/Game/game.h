//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_GAME_H
#define MAIN_C_GAME_H

#include "../rendering.h"

#define MAP_MARGIN 10
#define BORDER_THICKNESS 5;
#define MAP_PADDING 5

#define CELL_SIZE 10
#define CELL_MIN_MARGIN 4
enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum WindowState StartGame(GameRenderer *renderer);

#endif //MAIN_C_GAME_H
