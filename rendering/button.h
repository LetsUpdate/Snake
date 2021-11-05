//
// Created by János Tánczos on 2021. 11. 05..
//

#ifndef MAIN_C_BUTTON_H
#define MAIN_C_BUTTON_H

#include "rendering.h"
#include "SDL2_gfxPrimitives.h"



typedef struct Color{
    int r,g,b,a;
}Color;

typedef struct Button{
    struct Color textColor, color;
    Vector2 position;
    char text[10];
}Button;

typedef struct BoundaryBox{
    int x,y,x1,y1;
}BoundaryBox;

void RenderButton(GameRenderer* gameRenderer,Button button);

#endif //MAIN_C_BUTTON_H
