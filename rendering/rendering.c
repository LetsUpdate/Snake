//
// Created by János Tánczos on 2021. 11. 04..
//
#include "rendering.h"
#include "button.h"

GameRenderer InitGameRenderer() {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W,
                                          WINDOW_H, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    GameRenderer myRenderer = {renderer, MENU};
    return myRenderer;
}

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