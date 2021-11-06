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
    //todo ide kell doksi
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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
    //Load menu Items
    SDL_Texture * start_t =IMG_LoadTexture(renderer->renderer,R_START_BUTTON);
    SDL_Texture * score_t =IMG_LoadTexture(renderer->renderer,R_SCORE_BUTTON);
    SDL_Texture * exit_t =IMG_LoadTexture(renderer->renderer,R_EXIT_BUTTON);
    if(start_t==NULL||score_t==NULL||exit_t==NULL)
    {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }

    Button scoreButton= RenderButton(renderer, score_t, (Vector2){WINDOW_W / 2, WINDOW_H / 2});
    Button startButton = RenderButton(renderer, start_t, (Vector2){WINDOW_W /2, WINDOW_H / 4});
    Button exitButton = RenderButton(renderer, exit_t, (Vector2){WINDOW_W / 2, WINDOW_H / 2+WINDOW_H / 4});

    SDL_RenderPresent(renderer->renderer);
    SDL_DestroyTexture(start_t);
    SDL_DestroyTexture(score_t);
    SDL_DestroyTexture(exit_t);
    SDL_Event ev;
    bool click = false;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch (ev.type) {
            case SDL_MOUSEBUTTONDOWN:
                if(ev.button.button == SDL_BUTTON_LEFT) click=true;
                break;
            case SDL_MOUSEBUTTONUP:
                if(ev.button.button==SDL_BUTTON_LEFT){
                    if(click){
                        Vector2 mousePos={ev.motion.x,ev.motion.y};
                        if(DetectOverlap(&startButton,mousePos))
                            return GAME;
                        if(DetectOverlap(&scoreButton,mousePos))
                            return SCORE_BOARD;
                        if(DetectOverlap(&exitButton,mousePos))
                            return EXIt;
                    }
                    click=false;
                }
        }
    }
    return MENU;
}