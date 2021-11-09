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


enum WindowState StartGame(GameRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));
    Vector2 mapSize = {WINDOW_W / CELL_SIZE, WINDOW_H / CELL_SIZE};
    Vector2 startPos = {mapSize.x / 2, mapSize.y / 2};
    Snake snake = CreateSnake(startPos, 3);

    for (int i = 0; i < snake.length; i++) {
        Vector2 bodyPart = snake.body[i];
        bodyPart.x *= CELL_SIZE;
        bodyPart.y *= CELL_SIZE;
        boxRGBA(renderer->renderer, bodyPart.x, bodyPart.y, bodyPart.x + CELL_SIZE, bodyPart.y + CELL_SIZE, 255, 255,
                255, 255);
    }


    SDL_RenderPresent(renderer->renderer);
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {

    }
}

