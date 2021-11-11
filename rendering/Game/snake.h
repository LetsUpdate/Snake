//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_SNAKE_H
#define MAIN_C_SNAKE_H

#include "../rendering.h"
#include "game.h"
#include "../../debugmalloc.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


typedef struct Snake {
    Vector2 bodyPart;
    struct Snake* next;
} Snake;

Snake* CreateSnake(Vector2 startPos, int length);

bool MoveSnake(Snake *snake, enum Direction next);

Vector2 LastSnakeBody(Snake*snake);

void FreeSnake(Snake *snake);

void ExpandSnake(Snake *snake, Vector2 next);


#endif //MAIN_C_SNAKE_H
