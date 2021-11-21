//
// Created by János Tánczos on 2021. 11. 07..
//

#ifndef MAIN_C_GAME_H
#define MAIN_C_GAME_H

#include "../save_system.h"
#include "snake.h"
#include "stdlib.h"

struct GameRenderer;


#define CELL_SIZE 20

/// Full game loop, handles everything from rendering and game logic
/// @param renderer [in] constraints the SDL_renderer
enum WindowState StartGame(GameRenderer *renderer);

#endif //MAIN_C_GAME_H
