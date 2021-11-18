//
// Created by János Tánczos on 2021. 11. 18..
//

#ifndef MAIN_C_SAVE_SYSTEM_H
#define MAIN_C_SAVE_SYSTEM_H
#include "stdbool.h"
#include "./Game/snake.h"


#define SNAKE_DATA_FILE "snake.dat"
#define SCORE_BOARD_FILE "./score.dat"

/// Saves the snake'c current state to the disk
/// @param snake a Snake it self
bool SaveSnake(Snake * snake);
/// Loads the snake from the fs
/// @returns a "Snake" type linked list
Snake * loadSnake();


#endif //MAIN_C_SAVE_SYSTEM_H
