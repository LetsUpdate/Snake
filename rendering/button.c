//
// Created by János Tánczos on 2021. 11. 05..
//
#include "button.h"

Button RenderButton(GameRenderer *gameRenderer, SDL_Texture *texture, Vector2 pos) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect celterulet = {pos.x - w / 2, pos.y - h / 2, w, h};
    SDL_RenderCopy(gameRenderer->renderer, texture, NULL, &celterulet);
    //Normalise
    celterulet.h += celterulet.y;
    celterulet.w += celterulet.x;
    return (Button) {celterulet};
}

bool DetectOverlap(Button *button, Vector2 cursor) {
    SDL_Rect boundary = button->boundary;
    return (boundary.x < cursor.x && boundary.w > cursor.x && boundary.y < cursor.y && boundary.h > cursor.y);
}
