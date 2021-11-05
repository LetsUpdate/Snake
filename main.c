#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "rendering/rendering.h"
#include <stdbool.h>




int main(int argc, char *argv[]) {

    bool running=true;
    //Init Renderer
    GameRenderer myRenderer = InitGameRenderer();

    enum WindowState wState = OpenMenu(&myRenderer);
    SDL_Quit();

    return 0;
}