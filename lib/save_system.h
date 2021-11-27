//
// Created by János Tánczos on 2021. 11. 18..
//

#ifndef MAIN_C_SAVE_SYSTEM_H
#define MAIN_C_SAVE_SYSTEM_H

#include "stdbool.h"
#include "./Game/snake.h"


#define SNAKE_DATA_FILE "snake.dat"
#define SCORE_BOARD_FILE "./score.dat"
#define LENGTH_OF_NAME 10

typedef struct SnakeData {
    Snake *snake;
    enum Direction direction;
} SnakeData;


typedef struct Score {
    char *name;
    int value;
} Score;

typedef struct ScoreList {
    Score score;
    struct ScoreList *next;
} ScoreList;


/// Saves the snake'c current state to the disk
/// @param snake a Snake it self
bool SaveSnake(SnakeData snakeData);

/// Loads the snake from the fs
/// @returns a "Snake" type linked list
SnakeData LoadSnake();

void FreeScoreList(ScoreList *scoreList);

bool SaveScore(Score score);

ScoreList *LoadScore();


#endif //MAIN_C_SAVE_SYSTEM_H
