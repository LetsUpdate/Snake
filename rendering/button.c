//
// Created by János Tánczos on 2021. 11. 05..
//
#include "button.h"

void RectanglAround(SDL_Renderer * renderer, Vector2 pos,Color c){
    BoundaryBox boundaryBox;
    boundaryBox.x=pos.x-10;
    boundaryBox.x1=pos.x+10;
    boundaryBox.y=pos.y-10;
    boundaryBox.y1=pos.y+10;
    rectangleRGBA(renderer,boundaryBox.x,boundaryBox.y,boundaryBox.x1,boundaryBox.y1,c.r,c.g,c.b,c.a);
}

void RenderButton(GameRenderer* gameRenderer,Button button){
    stringRGBA(gameRenderer->renderer,button.position.x-10,button.position.y-5,button.text,button.color.r,button.color.g,button.textColor.b,button.color.a);
    RectanglAround(gameRenderer->renderer,button.position,button.color);

}
