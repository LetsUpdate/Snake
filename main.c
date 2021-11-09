#include <stdlib.h>
#include "debugmalloc.h"
#include "rendering/rendering.h"
#include "rendering/menu.h"
#include "rendering/Game/game.h"
#include <stdbool.h>


void Quit() {
    SDL_Quit();
    exit(0);
}

int main(int argc, char *argv[]) {
    if (WINDOW_W % CELL_SIZE != 0 || WINDOW_H % CELL_SIZE != 0) {
        printf("Scaling problems are expected...");
    }

    //Init Renderer
    GameRenderer myRenderer = InitGameRenderer();

    //App loop
    while (true) {
        enum WindowState wState = OpenMenu(&myRenderer);

        if (wState == EXIt)break;

        if (wState == GAME) {
            StartGame(&myRenderer);
        } else if (wState == SCORE_BOARD) {

        } else {
            printf("Unknown app state!, Quiting...");
            break;
        }
    }

    Quit();
    return 0;
}