#include "debugmalloc.h"
#include "lib/rendering.h"
#include "lib/Menu/menu.h"
#include "lib/Game/game.h"
#include "lib/Menu/scoreboard.h"
#include <stdbool.h>

#include "./lib/save_system.h"
void Quit() {
    SDL_Quit();
    exit(0);
}

int main(int argc, char *argv[]) {
#ifdef ScalingTest (WINDOW_W % CELL_SIZE != 0 || WINDOW_H % CELL_SIZE != 0)
    {
        printf("Scaling problems are expected...");
    }
#endif
    //Init Renderer
    GameRenderer myRenderer = InitGameRenderer();

    //App loop
    while (true) {
        enum WindowState wState = OpenMenu(&myRenderer);

        if (wState == EXIt)break;

        if (wState == GAME) {
            StartGame(&myRenderer);
        } else if (wState == SCORE_BOARD) {
            ShowScoreboard(&myRenderer);
        } else {
            printf("Unknown app state!, Quiting...");
            return 1;
        }
    }
    Quit();
    return 0;
}