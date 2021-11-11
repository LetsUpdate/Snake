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

int RandomInt(int max){
    return (((double) rand())/RAND_MAX) *(max);
}

Vector2 GenerateApple(Snake* forbiddenPlaces){
    Vector2 randomPos;
    randomPos.x = RandomInt(WINDOW_W/CELL_SIZE);
    randomPos.y = RandomInt(WINDOW_H/CELL_SIZE);
    Snake *tempPointer = forbiddenPlaces;
    while (tempPointer!=NULL){
        Vector2 b = tempPointer->bodyPart;
        if(b.x==randomPos.x&&b.y == randomPos.y){
            return GenerateApple(forbiddenPlaces);
        }
        tempPointer = tempPointer->next;
    }
    return randomPos;
}

enum WindowState StartGame(GameRenderer *renderer) {
    int points =0;

    //Pálya tisztítása
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear((renderer->renderer));
    SDL_TimerID timerId = SDL_AddTimer(300, timing, NULL);
    Vector2 mapSize = {WINDOW_W / CELL_SIZE, WINDOW_H / CELL_SIZE};
    Vector2 startPos = {mapSize.x / 2, mapSize.y / 2};

    Snake *snake = CreateSnake(startPos, 3);
    //render first snake
    Snake * sHead = snake;
    while (sHead!=NULL) {
        Vector2 bodyPart = snake->bodyPart;
        RenderCell(renderer,bodyPart,WHITE);
        sHead = sHead->next;
    }

    SDL_RenderPresent(renderer->renderer);
    SDL_Event ev;
    
    enum Direction direction =UP;
    enum Direction lastDirection=DOWN;
    Vector2 apple={-1,-1};
    //Game loop
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
            //Render and move snake in each tick
            case SDL_USEREVENT:
                //Utolsó rész eltüntetése
            {
                Vector2 head = snake->bodyPart;
                if (head.x == apple.x && head.y == apple.y) {
                    points++;
                    ExpandSnake(snake, direction);
                    apple = (Vector2) {-1, -1};
                } else {
                    RenderCell(renderer, LastSnakeBody(snake), BLACK);
                    MoveSnake(snake, direction);
                }

                //új fej meglenítése
                RenderCell(renderer, snake->bodyPart, WHITE);
                lastDirection = direction;
            }
                if(apple.x<0||apple.y<0) {
                    apple = GenerateApple(snake);
                    RenderCell(renderer,apple,RED);
                }
                SDL_RenderPresent(renderer->renderer);
                break;
        }

    }
    SDL_RemoveTimer(timerId);
    FreeSnake(snake);
}
