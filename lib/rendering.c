//
// Created by János Tánczos on 2021. 11. 04..
//
#include "rendering.h"
#include "Menu/button.h"
#include "../debugmalloc.h"

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

    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W,
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

void CreateRectangle(SDL_Renderer *renderer, Vector2 pos, Vector2 size, int r, int g, int b, int a) {
    roundedBoxRGBA(renderer, pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2, 10, r, g,
                   b, a);
}


Vector2 TextureSize(SDL_Texture *texture) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    return (Vector2) {w, h};
}

//IncfoC példaprogram alapján....
void RenderText(SDL_Renderer *renderer, char txt[], Vector2 pos) {
    TTF_Font *font = TTF_OpenFont("resources/orange juice.ttf", 32);
    if (font == NULL) {
        fprintf(stderr, "Unable to load the font becouse it's not found!\n");
        return;
    };
    /* felirat megrajzolasa, kulonfele verziokban */
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;



    /* ha sajat kodban hasznalod, csinalj belole fuggvenyt! */
    felirat = TTF_RenderUTF8_Blended(font, txt, (SDL_Color) {255, 255, 255, 255});
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    SDL_Rect location = {pos.x - felirat->w / 2, pos.y + felirat->h, 0, 0};
    location.w = felirat->w;
    location.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &location);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}

bool CreatePopUp(GameRenderer *renderer, char question[]) {
    //Load textures
    SDL_Texture *yes_t = IMG_LoadTexture(renderer->renderer, R_YES_BUTTON);
    SDL_Texture *no_t = IMG_LoadTexture(renderer->renderer, R_NO_BUTTON);

    Vector2 yes_size = TextureSize(yes_t);
    Vector2 no_size = TextureSize(no_t);
    int margin = 50;
    Vector2 size = {no_size.x + yes_size.x + margin, no_size.y + yes_size.y + margin};
    CreateRectangle(renderer->renderer, (Vector2) {WINDOW_W / 2, WINDOW_H / 2}, size, 0, 0, 0, 150);

    RenderText(renderer->renderer, question, (Vector2) {WINDOW_W / 2, WINDOW_H / 4});

    Button yesButton = RenderButton(renderer, yes_t, (Vector2) {WINDOW_W / 2 + yes_size.x - margin / 2,
                                                                WINDOW_H - WINDOW_H / 2 + yes_size.y});
    Button noButton = RenderButton(renderer, no_t, (Vector2) {WINDOW_W / 2 - yes_size.x + margin / 2,
                                                              WINDOW_H - WINDOW_H / 2 + no_size.y});

    //Render UI
    SDL_RenderPresent(renderer->renderer);

    //Unload textures
    SDL_DestroyTexture(yes_t);
    SDL_DestroyTexture(no_t);

    SDL_Event ev;
    //Waiting for input
    while (SDL_WaitEvent(&ev)) {
        switch (ev.type) {
            case SDL_MOUSEBUTTONUP:
                //Handle button clicks
                if (ev.button.button == SDL_BUTTON_LEFT) {
                    Vector2 mousePos = {ev.motion.x, ev.motion.y};
                    if (DetectOverlap(&yesButton, mousePos))
                        return true;
                    if (DetectOverlap(&noButton, mousePos))
                        return false;
                }
        }
    }
    return -1;
}
