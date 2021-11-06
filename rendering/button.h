//
// Created by János Tánczos on 2021. 11. 05..
//

#ifndef MAIN_C_BUTTON_H
#define MAIN_C_BUTTON_H

#include "rendering.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"


#define R_START_BUTTON "resources/play.png"
#define R_EXIT_BUTTON "resources/exit.png"
#define R_SCORE_BUTTON "resources/score_board.png"




typedef struct Color{
    int r,g,b,a;
}Color;

typedef struct BoundaryBox{
    int x,y,x1,y1;
}BoundaryBox;

typedef struct Button{
    SDL_Rect boundary;
}Button;

Button RenderButton(GameRenderer* gameRenderer,SDL_Texture * texture,Vector2 pos);

bool DetectOverlap(Button* button,Vector2 cursor);

#endif //MAIN_C_BUTTON_H
