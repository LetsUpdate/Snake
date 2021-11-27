//
// Created by János Tánczos on 2021. 11. 07..
//
#include "snake.h"
#include "game.h"

#define MALLOC_ERROR {printf(stderr,"memory malloc error\n"); return NULL;}


Snake *CreateSnake(Vector2 startPos, int length) {
    Snake *temp = NULL;
    for (int i = 0; i < length; ++i) {
        Snake *snake = malloc(sizeof(Snake));
        if (snake == NULL) MALLOC_ERROR
        snake->bodyPart = startPos;
        snake->next = temp;
        temp = snake;
    }
    return temp;
}

void FreeSnake(Snake *snake) {
    while (snake != NULL) {
        Snake *temp = snake->next;
        free(snake);
        snake = temp;
    }
}

Snake *AddElementToSnake(Snake *snake, Vector2 v) {
    Snake *temp = malloc(sizeof(Snake));
    if (temp == NULL) MALLOC_ERROR
    temp->bodyPart = v;
    temp->next = NULL;
    if (snake == NULL) {
        return temp;
    } else {
        Snake *head = snake;
        while (snake->next != NULL)snake = snake->next;
        snake->next = temp;
        snake = head;
    }
    return snake;
}

bool IsCollided(Snake *snake, Vector2 vector) {
    while (snake != NULL) {
        Vector2 body = snake->bodyPart;
        if (body.x == vector.x && body.y == vector.y) return true;
        snake = snake->next;
    }
    if (vector.y < 0 || vector.x < 0 || WINDOW_H / CELL_SIZE - 1 < vector.y || WINDOW_W / CELL_SIZE - 1 < vector.x)
        return true;
    return false;
}

Vector2 directionToVector(enum Direction direction, Vector2 head) {
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
        default:
            break;
    }
    return head;
}

bool MoveSnake(Snake *snake, enum Direction nextDirection) {
    Vector2 next = directionToVector(nextDirection, snake->bodyPart);
    if (IsCollided(snake, next))return false;
    while (snake != NULL) {
        Vector2 temp = snake->bodyPart;
        snake->bodyPart = next;
        next = temp;
        snake = snake->next;
    }
    return true;
}

Snake *getLastItem(Snake *snake) {
    while (snake->next != NULL)snake = snake->next;
    return snake;
}

Vector2 LastSnakeBody(Snake *snake) {
    return getLastItem(snake)->bodyPart;
}

void ExpandSnake(Snake *snake, Vector2 lastPart) {
    Snake *last = getLastItem(snake);
    Snake *newPart = malloc(sizeof(Snake));
    newPart->bodyPart = lastPart;
    newPart->next = NULL;
    last->next = newPart;
}
