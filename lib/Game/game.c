//
// Created by János Tánczos on 2021. 11. 07..
//
#include "game.h"
#include "../rendering.h"


enum Color {
    WHITE,
    BLACK,
    RED
};

void RenderCell(GameRenderer *renderer, Vector2 pos, enum Color color) {
    pos.x *= CELL_SIZE;
    pos.y *= CELL_SIZE;
    switch (color) {
        case WHITE:
            boxRGBA(renderer->renderer, pos.x, pos.y, pos.x + CELL_SIZE - 3, pos.y + CELL_SIZE - 3, 255, 255,
                    255, 255);
            break;
        case BLACK:
            boxRGBA(renderer->renderer, pos.x, pos.y, pos.x + CELL_SIZE - 3, pos.y + CELL_SIZE - 3, 0, 0,
                    0, 255);
            break;
        case RED:
            boxRGBA(renderer->renderer, pos.x, pos.y, pos.x + CELL_SIZE - 3, pos.y + CELL_SIZE - 3, 255, 0,
                    0, 255);
            break;
        default:
            boxRGBA(renderer->renderer, pos.x, pos.y, pos.x + CELL_SIZE - 1, pos.y + CELL_SIZE - 1, 0, 0,
                    0, 255);
    }
}

Uint32 timing(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

int RandomInt(int max) {
    return (((double) rand()) / RAND_MAX) * (max);
}

Vector2 GenerateApple(Snake *forbiddenPlaces) {
    Vector2 randomPos;
    randomPos.x = RandomInt(WINDOW_W / CELL_SIZE);
    randomPos.y = RandomInt(WINDOW_H / CELL_SIZE);
    Snake *tempPointer = forbiddenPlaces;
    while (tempPointer != NULL) {
        Vector2 b = tempPointer->bodyPart;
        if (b.x == randomPos.x && b.y == randomPos.y) {
            return GenerateApple(forbiddenPlaces);
        }
        tempPointer = tempPointer->next;
    }
    return randomPos;
}

enum Direction inverseDirection(enum Direction direction) {
    switch (direction) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        default:
            return UP;
    }
}

void RenderFullSnake(GameRenderer *renderer, Snake *snake) {
    Snake *sHead = snake;
    while (sHead != NULL) {
        Vector2 bodyPart = sHead->bodyPart;
        RenderCell(renderer, bodyPart, WHITE);
        sHead = sHead->next;
    }

    SDL_RenderPresent(renderer->renderer);
}

void ClearGameWindow(GameRenderer *renderer) {
    //Nem bug hanem FEATURE
    SDL_SetRenderDrawColor(renderer->renderer, 20, 30, 31, 255);
    SDL_RenderClear((renderer->renderer));
}

enum WindowState StartGame(GameRenderer *renderer) {
    int points = 0;

//Pálya tisztítása
    ClearGameWindow(renderer);

    SDL_TimerID timerId = SDL_AddTimer(300, timing, NULL);
    Vector2 mapSize = {WINDOW_W / CELL_SIZE, WINDOW_H / CELL_SIZE};
    Vector2 startPos = {mapSize.x / 2, mapSize.y / 2};

    //Load snake from disk
    Snake *snake = NULL;
    SnakeData snakeData = LoadSnake();
    if (snakeData.snake != NULL) {
        //Van mentés
        RenderFullSnake(renderer, snakeData.snake);
        if (CreatePopUp(renderer, "Folytatod?")) {
            snake = snakeData.snake;
        } else {
            FreeSnake(snakeData.snake);
        }
        ClearGameWindow(renderer);
    }


//render first snake
    if (snake == NULL) {
        snake = CreateSnake(startPos, 4);
    }

    ClearGameWindow(renderer);
    RenderFullSnake(renderer, snake);

    SDL_Event ev;

    enum Direction direction = (snakeData.snake == NULL) ? UP : snakeData.direction;
    enum Direction lastDirection = inverseDirection(direction);
    Vector2 apple = {-1, -1};
//Game loop
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch (ev.type) {
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                    case SDLK_UP:
                        if (lastDirection != DOWN)
                            direction = UP;
                        break;
                    case SDLK_DOWN:
                        if (lastDirection != UP)
                            direction = DOWN;
                        break;
                    case SDLK_LEFT:
                        if (lastDirection != RIGHT)
                            direction = LEFT;
                        break;
                    case SDLK_RIGHT:
                        if (lastDirection != LEFT)
                            direction = RIGHT;
                        break;
                }
                break;
//Render and move snake in each tick
            case SDL_USEREVENT:
//Utolsó rész eltüntetése
// Mozgás előre
            {/*Ha ez nincs itt nem jó :P*/}
                Vector2 lastSnakeBody = LastSnakeBody(snake);
                MoveSnake(snake, direction);
                Vector2 head = snake->bodyPart;
                if (head.x == apple.x && head.y == apple.y) {
                    points++;
                    ExpandSnake(snake, direction, lastSnakeBody);
                    apple = (Vector2) {-1, -1};
                    //RenderCell(renderer, snake->bodyPart, WHITE);
                } else {
                    RenderCell(renderer, lastSnakeBody, BLACK);
                }
                RenderCell(renderer, snake->bodyPart, WHITE);


                lastDirection = direction;
                //GenerateNewApple
                if (apple.x < 0 || apple.y < 0) {
                    apple = GenerateApple(snake);
                    RenderCell(renderer, apple, RED);
                }
                SDL_RenderPresent(renderer->renderer);
                break;
        }

    }
    SDL_RemoveTimer(timerId);
    SaveSnake((SnakeData) {snake, direction});
    FreeSnake(snake);
    return MENU;
}
