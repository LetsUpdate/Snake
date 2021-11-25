//
// Created by János Tánczos on 2021. 11. 05..
//

#ifndef MAIN_C_BUTTON_H
#define MAIN_C_BUTTON_H

#include "../rendering.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"

#define R_START_BUTTON "resources/play.png"
#define R_EXIT_BUTTON "resources/exit.png"
#define R_SCORE_BUTTON "resources/score_board.png"
#define R_YES_BUTTON "resources/yes.png"
#define R_NO_BUTTON "resources/no.png"

/// Constraints the boundary of the button
typedef struct Button {
    SDL_Rect boundary;
} Button;

/// Creates a button on the scene
/// @param gameRenderer is the renderer
/// @param texture SDL_Texture of an image
/// @param pos the position of the button (center)
/// @return a Button it self
Button RenderButton(GameRenderer *gameRenderer, SDL_Texture *texture, Vector2 pos);

/// Detect the overlap of the given Button and a Vector2
/// @param button
/// @param cursor
/// @returns true if there is overlap and false if there in not
bool DetectOverlap(Button *button, Vector2 cursor);


#endif //MAIN_C_BUTTON_H
