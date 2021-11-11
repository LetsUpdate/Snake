//
// Created by János Tánczos on 2021. 11. 07..
//
#include "game.h"


enum Color{
    WHITE,
    BLACK,
    RED
};

void RenderCell(GameRenderer *renderer, Vector2 pos, enum Color color){
    pos.x *= CELL_SIZE;
    pos.y *= CELL_SIZE;
    switch (color) {
        case WHITE:
            boxRGBA(renderer->renderer, pos.x,pos.y, pos.x + CELL_SIZE-3, pos.y + CELL_SIZE-3, 255, 255,
                    255, 255);
            break;
        case BLACK:
            boxRGBA(renderer->renderer, pos.x,pos.y, pos.x + CELL_SIZE-3, pos.y + CELL_SIZE-3, 0, 0,
                    0, 255);
            break;
        case RED:
            boxRGBA(renderer->renderer, pos.x,pos.y, pos.x + CELL_SIZE-3, pos.y + CELL_SIZE-3, 255, 0,
                    0, 255);
            break;
        default:boxRGBA(renderer->renderer, pos.x,pos.y, pos.x + CELL_SIZE-1, pos.y + CELL_SIZE-1, 0, 0,
                        0, 255);
    }
}

Uint32 timing(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}


enum WindowState StartGame(GameRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));
    Vector2 mapSize = {WINDOW_W / CELL_SIZE, WINDOW_H / CELL_SIZE};
    Vector2 startPos = {mapSize.x / 2, mapSize.y / 2};
    Snake *snake = CreateSnake(startPos, 40);

    SDL_TimerID timerId = SDL_AddTimer(300, timing, NULL);
    Snake * head = snake;
    while (head!=NULL) {
        Vector2 bodyPart = snake->bodyPart;
        RenderCell(renderer,bodyPart,WHITE);
        head = head->next;
    }



    SDL_RenderPresent(renderer->renderer);
    SDL_Event ev;
    
    enum Direction direction =UP;
    enum Direction lastDirection=DOWN;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch (ev.type) {
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                    case SDLK_UP:
                        if(lastDirection!=DOWN)
                        direction=UP;
                        break;
                    case SDLK_DOWN:
                        if(lastDirection!=UP)
                        direction=DOWN;
                        break;
                    case SDLK_LEFT:
                        if(lastDirection!=RIGHT)
                        direction=LEFT;
                        break;
                    case SDLK_RIGHT:
                        if(lastDirection!=LEFT)
                        direction=RIGHT;
                        break;
                }
                break;
            case SDL_USEREVENT:

                RenderCell(renderer,LastSnakeBody(snake),BLACK);

                MoveSnake(snake,direction);
                RenderCell(renderer,snake->bodyPart,WHITE);
                lastDirection=direction;

                SDL_RenderPresent(renderer->renderer);
                break;
        }

    }
    SDL_RemoveTimer(timerId);
    FreeSnake(snake);
}

