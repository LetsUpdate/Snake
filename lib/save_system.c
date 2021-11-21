//
// Created by János Tánczos on 2021. 11. 18..
//
#include "save_system.h"


bool SaveSnake(SnakeData snakeData) {
    FILE *file = fopen(SNAKE_DATA_FILE, "w");
    Snake *snake = snakeData.snake;
    //error handling
    if (file == NULL) {
        perror("Nem sikerült megnyitni a SNAKE_DATA fájlt");
        return false;
    }
    int count = 0;
    // writing to file
    fprintf(file, "%d\n", snakeData.direction);
    while (snake != NULL) {
        fprintf(file, "%d,%d\n", snake->bodyPart.x, snake->bodyPart.y);
        snake = snake->next;
        count++;
    }
    //close
    fclose(file);
}

SnakeData LoadSnake() {
    FILE *file = fopen(SNAKE_DATA_FILE, "r");
    if (file == NULL) {
        return (SnakeData) {NULL, 0};
    }
    Vector2 vector2;
    Snake *newSnake = NULL;
    int direction;
    fscanf(file, "%d", &direction);
    while (EOF != fscanf(file, "%d,%d", &vector2.x, &vector2.y)) {
        newSnake = AddElementToSnake(newSnake, vector2);
    }
    //The save is not valid anymore so...
    remove(SNAKE_DATA_FILE);
    return (SnakeData) {newSnake, direction};
}


