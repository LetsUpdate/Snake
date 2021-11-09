//
// Created by János Tánczos on 2021. 11. 07..
//
#include "snake.h"

Snake CreateSnake(Vector2 startPos, int length) {
    Vector2 *snakeBody = malloc(sizeof(Vector2) * length);
    for (int i = 0; i < length; i++)
        snakeBody[i] = startPos;
    Snake newSnake = (Snake) {snakeBody, length, length - 1};
    return newSnake;
}

void FreeSnake(Snake *snake) {
    free(snake->body);
}

bool IsCollided(Snake *snake, Vector2 vector) {
    for (int i = 0; i < snake->length; i++) {
        Vector2 v = snake->body[i];
        if (v.x == vector.x && v.y == vector.y)return true;
    }
    //todo handle walls
    return false;
}

bool MoveSnake(Snake *snake, Vector2 next) {
    if (IsCollided(snake, next))return false;
    snake->body[snake->lastBodyPartIndex] = next;
    snake->lastBodyPartIndex--;
    if (snake->lastBodyPartIndex < 0) snake->lastBodyPartIndex = snake->length - 1;
    return true;
}

void ExpandSnake(Snake *snake, Vector2 next) {
    snake->length++;
    Vector2 *newBody = malloc(sizeof(Vector2) * snake->length);
    for (int i = 0; i < snake->length - 1; i++) {
        newBody[i] = snake->body[i];
    }
    newBody[snake->length - 1] = next;
    FreeSnake(snake);
    snake->body = newBody;
}
