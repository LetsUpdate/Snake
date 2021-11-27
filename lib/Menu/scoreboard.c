//
// Created by János Tánczos on 2021. 11. 25..
//

#include "scoreboard.h"


void ShowScoreboard(GameRenderer *renderer) {
    //Load
    ScoreList *scoreList = LoadScore();
    TTF_Font *font = LoadFont();
    int i = 0;
    ScoreList *pointerSaver = scoreList;
    //Render
    while (scoreList != NULL) {
        Score score = scoreList->score;
        Vector2 posTex, posScore;
        if (i < 8) {
            posTex = (Vector2) {50, i * 40};
            posScore = (Vector2) {posTex.x + 60, posTex.y};
        } else {
            posScore = (Vector2) {WINDOW_W - 20, (i - 8) * 40};
            posTex = (Vector2) {posScore.x - 60, posScore.y};
            if (i > 16)
                break;

        }
        RenderText(renderer->renderer, font, score.name, posTex, 1);

        char *sPoints = malloc(sizeof(char) * (score.value / 10 + 2));
        sPoints[0] = '\0';
        sprintf(sPoints, "%d", score.value);

        RenderText(renderer->renderer, font, sPoints, posScore, 1);
        free(sPoints);

        scoreList = scoreList->next;
        i++;
    }
    SDL_RenderPresent(renderer->renderer);
    //Clear
    FreeScoreList(pointerSaver);
    TTF_CloseFont(font);
    //Wait for click
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch (ev.type) {
            case SDL_MOUSEBUTTONUP:
                return;
        }
    }
}
