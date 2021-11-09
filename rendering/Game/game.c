//
// Created by János Tánczos on 2021. 11. 07..
//
#include "game.h"

typedef struct Map{
    int ** cells;
    Vector2 size;
}Map;

Map CreateMap(SDL_Rect trueGameSpace){
    int horizontalCellCount =  (trueGameSpace.w-trueGameSpace.x)/(CELL_SIZE+CELL_MIN_MARGIN);
    int verticalCellCount = (trueGameSpace.h-trueGameSpace.y)/(CELL_SIZE+CELL_MIN_MARGIN);
    Vector2 size ={horizontalCellCount,verticalCellCount};

    int**cells = (double**) malloc(horizontalCellCount * sizeof(double*));
    for (int y = 0; y < horizontalCellCount; ++y)
        cells[y] = (double*) malloc(verticalCellCount * sizeof(double));

    return (Map){cells,size};
}
void FreeMap(Map* map){
    for (int y = 0; y < map->size.y; ++y)
        free(map->cells[y]);
    free(map->cells);
}


enum WindowState StartGame(GameRenderer *renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));
    for (int i = 0; i < BORDER_THICKNESS; i++) {
        rectangleRGBA(renderer->renderer, MAP_MARGIN + i, MAP_MARGIN + i, WINDOW_W - MAP_MARGIN - i, WINDOW_H - MAP_MARGIN - i, 255, 255, 255, 255);
    }
    int AllPadding =MAP_PADDING+MAP_MARGIN+BORDER_THICKNESS;

    SDL_Rect trueGameSpace =(SDL_Rect){AllPadding,AllPadding,WINDOW_W-AllPadding,WINDOW_H-AllPadding};


    SDL_RenderPresent(renderer->renderer);
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT){

    }
}

