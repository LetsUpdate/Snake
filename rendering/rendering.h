//
// Created by János Tánczos on 2021. 11. 04..
//

#ifndef MAIN_C_RENDERING_H
#define MAIN_C_RENDERING_H
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "stdbool.h"


enum WindowState{
    GAME,
    MENU,
    SCORE_BOARD,
    EXIt
};

typedef struct GameRenderer{
    SDL_Renderer* renderer;
    enum WindowState state;

}GameRenderer;

typedef struct Vector2{
    int x,y;
}Vector2;


GameRenderer InitGameRenderer();

enum WindowState OpenMenu(GameRenderer* renderer);

#endif //MAIN_C_RENDERING_H
