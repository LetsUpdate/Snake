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
    if(vector.y<0||vector.x<0||WINDOW_H/CELL_SIZE -1<vector.y||WINDOW_W/CELL_SIZE -1<vector.x)
        return true;
    return false;
}

Vector2 directionToVector(enum Direction direction,Vector2 head){
    switch (direction) {

        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        default:break;
    }
    return head;
}

Vector2 GetSnakeHead(Snake*snake){
    return snake->body[snake->headIndex];
}

bool MoveSnake(Snake *snake, enum Direction nextDirection) {

    Vector2 next = directionToVector(nextDirection, GetSnakeHead(snake));
    if (IsCollided(snake, next))return false;
    snake->body[snake->lastBodyPartIndex] = next;
    snake->headIndex=snake->lastBodyPartIndex;
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
