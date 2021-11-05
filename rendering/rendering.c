//
// Created by János Tánczos on 2021. 11. 04..
//
#include "rendering.h"
#include "button.h"

#define WINDOW_W 440
#define WINDOW_H 360

GameRenderer InitGameRenderer(){
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
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
    GameRenderer myRenderer = {renderer,  MENU};
    return myRenderer;
}


enum WindowState OpenMenu(GameRenderer* renderer){
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));
    //todo Render Menu


    struct Color textColor={255,255,255,255};
    struct Color buttonColor = {0,255,0,255};
    Vector2 pos ={WINDOW_W/2,WINDOW_H/2};
    Button testButton=(Button){textColor,buttonColor,pos,"asd"};
    RenderButton(renderer, testButton);


    SDL_RenderPresent(renderer->renderer);
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {

    }
    return MENU;
}