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

/// Creates a "pop-up" like dialog, with a yes or no question
/// @param renderer the GameRenderer
/// @param question a char array
/// @returns the answer of the Yes-no question
bool CreatePopUp(GameRenderer *renderer, char question[]);

/// Creates a "pop-up" like dialog, with an input field
/// @param renderer the GameRenderer
/// @param title a char array what will be the title of the dialog
/// @param subTitle a smaller title  for more info
char *CreateInputPopUp(GameRenderer *renderer, char title[], char subTitle[]);

/// Loads a font from the disk
/// @returns TTF_Font pointer
TTF_Font *LoadFont();

/// Gets the size of a texture
/// @param texture
/// @returns a Vector2 with the dimensions
Vector2 GetTextureSize(SDL_Texture *texture);

/// Renders the text to the screen
/// @param renderer
/// @param font the loaded font
/// @param txt the text to be rendered
/// @param pos the position of the text
/// @param size the scale of the text "1" is the normal
void RenderText(SDL_Renderer *renderer, TTF_Font *font, char txt[], Vector2 pos, float size);

/// Copied from infoC
/// Generates an input text field
/// @param dest the destination of the result
/// @param hossz it must be smaller than the lenght of the destination
/// @param teglalap what surrounds the  input-field
/// @param hatter the color of the background
/// @param szoveg the color of the txt
/// @param font the font of the text
/// @param renderer
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font,
                SDL_Renderer *renderer);

#endif //MAIN_C_RENDERING_H