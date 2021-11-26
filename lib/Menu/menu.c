//
// Created by János Tánczos on 2021. 11. 07..
//

#include "menu.h"


enum WindowState OpenMenu(GameRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));

    //Load menu Item textures
    SDL_Texture *start_t = IMG_LoadTexture(renderer->renderer, R_START_BUTTON);
    SDL_Texture *score_t = IMG_LoadTexture(renderer->renderer, R_SCORE_BUTTON);
    SDL_Texture *exit_t = IMG_LoadTexture(renderer->renderer, R_EXIT_BUTTON);
    if (start_t == NULL || score_t == NULL || exit_t == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }

    TTF_Font *font = LoadFont();
    RenderText(renderer->renderer, font, "SNAKE", (Vector2) {WINDOW_W / 2, 0}, 1);

    //create buttons
    Button scoreButton = RenderButton(renderer, score_t, (Vector2) {WINDOW_W / 2, (WINDOW_H + 40) / 2});
    Button startButton = RenderButton(renderer, start_t, (Vector2) {WINDOW_W / 2, (WINDOW_H + 120) / 4});
    Button exitButton = RenderButton(renderer, exit_t,
                                     (Vector2) {WINDOW_W / 2, (WINDOW_H + 10) / 2 + (WINDOW_H + 10) / 4});

    //render screen
    SDL_RenderPresent(renderer->renderer);
    //destroy already rendered items and saving memory
    SDL_DestroyTexture(start_t);
    SDL_DestroyTexture(score_t);
    SDL_DestroyTexture(exit_t);
    TTF_CloseFont(font);

    SDL_Event ev;

    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch (ev.type) {
            case SDL_MOUSEBUTTONUP:
                //Handle button clicks
                if (ev.button.button == SDL_BUTTON_LEFT) {
                    Vector2 mousePos = {ev.motion.x, ev.motion.y};
                    if (DetectOverlap(&startButton, mousePos))
                        return GAME;
                    if (DetectOverlap(&scoreButton, mousePos))
                        return SCORE_BOARD;
                    if (DetectOverlap(&exitButton, mousePos))
                        return EXIt;
                }
        }
    }
    return EXIt;
}