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

/// A package for the snake to help loading/saving
typedef struct SnakeData {
    Snake *snake;
    enum Direction direction;
} SnakeData;

/// Score struct
typedef struct Score {
    char *name;
    int value;
} Score;

/// A linked list from Score structs, represents a package what will be saved
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

/// frees the ScoreList
/// @param scoreList what you wanna set free
void FreeScoreList(ScoreList *scoreList);

/// Save the score to the disk
/// @param score
/// @returns true if succeeded and false if not
bool SaveScore(Score score);

/// Loads the score from the disk
/// @returns a linked list with the scores
/// @attention you have to free the returned list after use, with FreeScoreList()
ScoreList *LoadScore();


#endif //MAIN_C_SAVE_SYSTEM_H
