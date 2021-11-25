//
// Created by János Tánczos on 2021. 11. 04..
//

#ifndef MAIN_C_RENDERING_H
#define MAIN_C_RENDERING_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "stdbool.h"

#define WINDOW_W 440
#define WINDOW_H 360

/// States of the app window
enum WindowState {
    GAME,
    MENU,
    SCORE_BOARD,
    EXIt
};
/// Constraints everything what essential info tu rendering
typedef struct GameRenderer {
    SDL_Renderer *renderer;
    enum WindowState state;
} GameRenderer;

/// A 2D vector with X and Y coordinates
typedef struct Vector2 {
    int x, y;
} Vector2;

/// Initialize the renderer this step makes the program graphical
/// @return a GameRenderer object what used in every other rendering specific task
GameRenderer InitGameRenderer();

bool CreatePopUp(GameRenderer *renderer, char question[]);

char *CreateInputPopUp(GameRenderer *renderer, char title[], char question[]);

Vector2 TextureSize(SDL_Texture *texture);

void RenderText(SDL_Renderer *renderer, TTF_Font *font, char txt[], Vector2 pos, float size);

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font,
                SDL_Renderer *renderer);

#endif //MAIN_C_RENDERING_H