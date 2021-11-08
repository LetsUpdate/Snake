//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_SNAKE_H
#define MAIN_C_SNAKE_H
#include "../rendering.h"

typedef struct Snake{
    Vector2 * body;
    int length;
    int lastBodyPartIndex;
}Snake;

Snake CreateSnake(Vector2 startPos,int length);
bool MoveSnake(Snake *snake,Vector2 next);
void ExpandSnake(Snake *snake,Vector2 next);


#endif //MAIN_C_SNAKE_H
