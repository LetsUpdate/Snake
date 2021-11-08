//
// Created by János Tánczos on 2021. 11. 07..
//
#include "game.h"


enum WindowState StartGame(GameRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));
    for (int i = 0; i < 10; i++) {
        rectangleRGBA(renderer->renderer, 5 + i, 5 + i, WINDOW_W - 5 - i, WINDOW_H - 5 - i, 255, 255, 255, 255);
    }
    SDL_RenderPresent(renderer->renderer);
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT);
}

