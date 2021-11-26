//
// Created by János Tánczos on 2021. 11. 04..
//
#include "rendering.h"
#include "Menu/button.h"
#include "../debugmalloc.h"

GameRenderer InitGameRenderer() {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W,
                                          WINDOW_H, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    GameRenderer myRenderer = {renderer, MENU};
    return myRenderer;
}

TTF_Font *LoadFont() {
    return TTF_OpenFont("resources/orange juice.ttf", 32);
}

void CreateRectangle(SDL_Renderer *renderer, Vector2 pos, Vector2 size, int r, int g, int b, int a) {
    roundedBoxRGBA(renderer,
                   pos.x - size.x / 2,
                   pos.y - size.y / 2,
                   pos.x + size.x / 2,
                   pos.y + size.y / 2,
                   10, r, g, b, a);
}

Vector2 GetTextureSize(SDL_Texture *texture) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    return (Vector2) {w, h};
}

//IncfoC példaprogram alapján....
void RenderText(SDL_Renderer *renderer, TTF_Font *font, char txt[], Vector2 pos, float size) {
    if (font == NULL) {
        fprintf(stderr, "Unable to load the font becouse it's not found!\n");
        return;
    };
    /* felirat megrajzolasa, kulonfele verziokban */
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;

    /* ha sajat kodban hasznalod, csinalj belole fuggvenyt! */
    felirat = TTF_RenderUTF8_Blended(font, txt, (SDL_Color) {255, 255, 255, 255});
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    SDL_Rect location = {pos.x - felirat->w / 2, pos.y + felirat->h, 0, 0};
    location.w = felirat->w * size;
    location.h = felirat->h * size;
    SDL_RenderCopy(renderer, felirat_t, NULL, &location);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}

bool CreatePopUp(GameRenderer *renderer, char question[]) {
    //Load textures
    SDL_Texture *yes_t = IMG_LoadTexture(renderer->renderer, R_YES_BUTTON);
    SDL_Texture *no_t = IMG_LoadTexture(renderer->renderer, R_NO_BUTTON);

    Vector2 yes_size = GetTextureSize(yes_t);
    Vector2 no_size = GetTextureSize(no_t);
    int margin = 50;
    Vector2 size = {
            no_size.x + yes_size.x + margin,
            no_size.y + yes_size.y + margin};
    CreateRectangle(renderer->renderer,
                    (Vector2) {WINDOW_W / 2, WINDOW_H / 2}, size,
                    0, 0, 0, 150);
    TTF_Font *font = LoadFont();
    RenderText(renderer->renderer, font, question,
               (Vector2) {WINDOW_W / 2, WINDOW_H / 4},
               1);

    Button yesButton = RenderButton(renderer, yes_t, (Vector2) {
            WINDOW_W / 2 + no_size.x - margin / 2,
            WINDOW_H - WINDOW_H / 2 + yes_size.y});
    Button noButton = RenderButton(renderer, no_t, (Vector2) {
            WINDOW_W / 2 - no_size.x + margin / 2,
            WINDOW_H - WINDOW_H / 2 + no_size.y});

    //Render UI
    SDL_RenderPresent(renderer->renderer);

    //Unload textures
    SDL_DestroyTexture(yes_t);
    SDL_DestroyTexture(no_t);
    TTF_CloseFont(font);
    SDL_Event ev;
    //Waiting for input
    while (SDL_WaitEvent(&ev)) {
        switch (ev.type) {
            case SDL_MOUSEBUTTONUP:
                //Handle button clicks
                if (ev.button.button == SDL_BUTTON_LEFT) {
                    Vector2 mousePos = {ev.motion.x, ev.motion.y};
                    if (DetectOverlap(&yesButton, mousePos))
                        return true;
                    if (DetectOverlap(&noButton, mousePos))
                        return false;
                }
        }
    }
    return -1;
}

char *CreateInputPopUp(GameRenderer *renderer, char title[], char subTitle[]) {
    //Load textures
    int margin = 50;

    SDL_Rect teglalap = {WINDOW_W / 2 - WINDOW_W / 3 / 2, WINDOW_H / 2 + 20, WINDOW_W / 3, 32};
    Vector2 size = {teglalap.w + 100, WINDOW_H / 3};
    CreateRectangle(renderer->renderer, (Vector2) {WINDOW_W / 2, WINDOW_H / 2}, size, 0, 0, 0, 150);

    TTF_Font *font = LoadFont();
    RenderText(renderer->renderer, font, title, (Vector2) {WINDOW_W / 2, WINDOW_H / 4}, 1);
    RenderText(renderer->renderer, font, subTitle, (Vector2) {WINDOW_W / 2, WINDOW_H / 4 + 30}, 1);

    SDL_Color black = {0, 0, 0, 20}, white = {255, 255, 255, 255};

    char *out = malloc(sizeof(char) * 11);
    out[0] = '\0';

    bool success = input_text(out, 10, teglalap, black, white, font, renderer->renderer);

    //Render UI
    SDL_RenderPresent(renderer->renderer);

    TTF_CloseFont(font);

    SDL_Event ev;
    //Waiting for input
    //Csak egy bug miatt
    SDL_RenderPresent(renderer->renderer);
    if (success)
        if (strlen(out) > 0)
            return out;
    return NULL;
}

/* Beolvas egy szoveget a billentyuzetrol.
 * A rajzolashoz hasznalt font es a megjelenito az utolso parameterek.
 * Az elso a tomb, ahova a beolvasott szoveg kerul.
 * A masodik a maximális hossz, ami beolvasható.
 * A visszateresi erteke logikai igaz, ha sikerult a beolvasas. */
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font,
                SDL_Renderer *renderer) {
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter) {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r,
                hatter.g, hatter.b, hatter.a);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1,
                      szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0') {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = {teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw,
                            felirat->h < maxh ? felirat->h : maxh};
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        } else {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw) {
            vlineRGBA(renderer,
                      teglalap.x + w + 2, teglalap.y + 2,
                      teglalap.y + teglalap.h - 3,
                      szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* Kulonleges karakter */
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen - 1] & 0x80) == 0x00) {
                            /* Egy bajt */
                            dest[textlen - 1] = 0x00;
                            break;
                        }
                        if ((dest[textlen - 1] & 0xC0) == 0x80) {
                            /* Bajt, egy tobb-bajtos szekvenciabol */
                            dest[textlen - 1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen - 1] & 0xC0) == 0xC0) {
                            /* Egy tobb-bajtos szekvencia elso bajtja */
                            dest[textlen - 1] = 0x00;
                            break;
                        }
                    } while (true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    enter = true;
                }
                break;

                /* A feldolgozott szoveg bemenete */
            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(event.text.text) < hossz) {
                    strcat(dest, event.text.text);
                }

                /* Az eddigi szerkesztes torolheto */
                composition[0] = '\0';
                break;

                /* Szoveg szerkesztese */
            case SDL_TEXTEDITING:
                strcpy(composition, event.edit.text);
                break;

            case SDL_QUIT:
                /* visszatesszuk a sorba ezt az eventet, mert
                 * sok mindent nem tudunk vele kezdeni */
                SDL_PushEvent(&event);
                kilep = true;
                break;
        }
    }

    /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    SDL_StopTextInput();
    return enter;
}
