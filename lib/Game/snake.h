//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_SNAKE_H
#define MAIN_C_SNAKE_H

#include "../rendering.h"
#include "../../debugmalloc.h"

/// Direction
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
/// A linked list as the snake
typedef struct Snake {
    Vector2 bodyPart;
    struct Snake *next;
} Snake;

/// Creates the snake from scratch
/// @param startPos the coordinates of the whole Snake
/// @param length the initialization length if the Snake
/// @returns A Snake struct what it self is a linked list
/// @attention You have to Free the snake with the FreeSnake function
Snake *CreateSnake(Vector2 startPos, int length);

/// Moves the snake to the given direction
/// @param snake the snake is Self
/// @param nextDirection direction of the move
bool MoveSnake(Snake *snake, enum Direction next);

/// Returns the last body part's postion
/// @param snake
/// @returns true if the move can be done, and false if something is blocking the snake it self
Vector2 LastSnakeBody(Snake *snake);

/// Frees the snake
/// @param snake
void FreeSnake(Snake *snake);


/// Ads an elemt to the snake, (it can be used to create a snake it self)
Snake *AddElementToSnake(Snake *snake, Vector2 v);

/// Expands the snake to the given direction
/// @param snake the snake is Self
/// @param nextDirection direction of the expansion
void ExpandSnake(Snake *snake, Vector2 last);

#endif //MAIN_C_SNAKE_H
