//
// Created by János Tánczos on 2021. 11. 07..
//
#include "game.h"

typedef struct Map {
    int **cells;
    Vector2 size;
} Map;

Map CreateMap(SDL_Rect trueGameSpace) {
    int horizontalCellCount = (trueGameSpace.w - trueGameSpace.x) / (CELL_SIZE);
    int verticalCellCount = (trueGameSpace.h - trueGameSpace.y) / (CELL_SIZE);
    Vector2 size = {horizontalCellCount, verticalCellCount};

    int **cells = (double **) malloc(horizontalCellCount * sizeof(double *));
    for (int y = 0; y < horizontalCellCount; ++y)
        cells[y] = (double *) malloc(verticalCellCount * sizeof(double));

    return (Map) {cells, size};
}

void FreeMap(Map *map) {
    for (int y = 0; y < map->size.y; ++y)
        free(map->cells[y]);
    free(map->cells);
}

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
    Snake snake = CreateSnake(startPos, 40);

    SDL_TimerID timerId = SDL_AddTimer(300, timing, NULL);

    for (int i = 0; i < snake.length; i++) {
        Vector2 bodyPart = snake.body[i];
        RenderCell(renderer,bodyPart,WHITE);
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

                RenderCell(renderer,snake.body[snake.lastBodyPartIndex],BLACK);

                MoveSnake(&snake,direction);
                RenderCell(renderer,snake.body[snake.headIndex],WHITE);
                lastDirection=direction;

                SDL_RenderPresent(renderer->renderer);
                break;
        }

    }
    SDL_RemoveTimer(timerId);
}

