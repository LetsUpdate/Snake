//
// Created by János Tánczos on 2021. 11. 18..
//
#include "save_system.h"


bool SaveSnake(SnakeData snakeData) {
    FILE *file = fopen(SNAKE_DATA_FILE, "w");
    Snake *snake = snakeData.snake;
    //error handling
    if (file == NULL) {
        perror("Nem sikerült megnyitni a SNAKE_DATA fájlt");
        return false;
    }
    int count = 0;
    // writing to file
    fprintf(file, "%d\n", snakeData.direction);
    while (snake != NULL) {
        fprintf(file, "%d,%d\n", snake->bodyPart.x, snake->bodyPart.y);
        snake = snake->next;
        count++;
    }
    //close
    fclose(file);
    return true;
}

SnakeData LoadSnake() {
    FILE *file = fopen(SNAKE_DATA_FILE, "r");
    if (file == NULL) {
        return (SnakeData) {NULL, 0};
    }
    Vector2 vector2;
    Snake *newSnake = NULL;
    int direction;
    fscanf(file, "%d", &direction);
    while (EOF != fscanf(file, "%d,%d", &vector2.x, &vector2.y)) {
        newSnake = AddElementToSnake(newSnake, vector2);
    }
    //The save is not valid anymore so...
    remove(SNAKE_DATA_FILE);
    return (SnakeData) {newSnake, direction};
}

void addToScoreList(ScoreList **list, Score score) {
    ScoreList *newList = *list;
    //If null create a new list
    if (newList == NULL) {
        newList = malloc(sizeof(ScoreList));
        newList->score = score;
        newList->next = NULL;
        *list = newList;
        return;
    }

    //ha az első elem egyezik a ponttal akkor legyen egyenlő vele és kész vagyunk!
    if (strcmp(newList->score.name, score.name) == 0)
        if (newList->score.value < score.value) {
            newList->score = score;
            return;
        }
    ScoreList *tempList = newList;
    ScoreList *lastElement;
    //
    while (tempList != NULL) {
        if (strcmp(tempList->score.name, score.name) == 0) {
            //if exists and its score is the same or lover then nothing to do
            if (tempList->score.value >= score.value)return;
            // else... Remove temporarily from the list
            //Removed from the linked list its time to reorder
            lastElement->next = tempList->next;
            free(tempList->score.name);
            free(tempList);
            tempList = NULL;
            break;
        }
        lastElement = tempList;
        tempList = tempList->next;

    }
    //Everything is set up the list is clean, it is time to insert the score to the right place
    tempList = newList;
    lastElement = NULL;
    if (score.value >= tempList->score.value) {
        //if score is greater or equal to the highest value
        ScoreList *newItem = malloc(sizeof(ScoreList));
        newItem->score = score;
        newItem->next = newList;
        (*list) = newItem;
        return;
    }
    while (tempList != NULL) {
        if (tempList->score.value <= score.value) {
            ScoreList *newElement = malloc(sizeof(ScoreList));
            lastElement->next = newElement;
            newElement->next = tempList;
            newElement->score = score;
            return;
        }

        //Ha a legutolsó elemnél is kisebb
        if (tempList->next == NULL) {
            ScoreList *newElement = malloc(sizeof(ScoreList));
            newElement->score = score;
            newElement->next = NULL;
            tempList->next = newElement;
            return;
        }
        lastElement = tempList;
        tempList = tempList->next;
    }
}

bool SaveScore(Score score) {
    //Load from disk
    ScoreList *scoreList = LoadScore();
    //place to the right place
    addToScoreList(&scoreList, score);
    //Override the whole file
    FILE *file = fopen(SCORE_BOARD_FILE, "w");
    if (file == NULL)return false;
    ScoreList *tempScoreList = scoreList;
    while (tempScoreList != NULL) {
        fprintf(file, "%d|%s\n", tempScoreList->score.value, tempScoreList->score.name);
        tempScoreList = tempScoreList->next;
    }
    //Close, and free up;
    fclose(file);
    FreeScoreList(scoreList);
    return true;
}

/// this function is jut to make faster the load from disk;
void AddToScoreListSimple(ScoreList **list, Score score) {
    ScoreList *realList = *list;
    if (realList == NULL) {
        realList = malloc(sizeof(ScoreList));
        realList->score = score;
        realList->next = NULL;
        *list = realList;
        return;
    }
    while (realList->next != NULL) {
        realList = realList->next;
    }
    ScoreList *tempElement = malloc(sizeof(ScoreList));
    tempElement->score = score;
    tempElement->next = NULL;
    realList->next = tempElement;
}

ScoreList *LoadScore() {
    //Opens the file
    FILE *file = fopen(SCORE_BOARD_FILE, "r");
    if (file == NULL)return NULL;
    Score tempScore;
    ScoreList *scoreList = NULL;
    tempScore.name = malloc(sizeof(char) * (LENGTH_OF_NAME + 1));
    //Read from disk
    while (EOF != fscanf(file, "%d|%s", &tempScore.value, tempScore.name)) {
        Score score;
        score.value = tempScore.value;
        score.name = malloc(sizeof(char) * (LENGTH_OF_NAME + 1));
        score.name[0] = '\0';
        strcpy(score.name, tempScore.name);
        AddToScoreListSimple(&scoreList, score);
    }
    //free and close
    free(tempScore.name);
    fclose(file);
    return scoreList;
}

void FreeScoreList(ScoreList *scoreList) {
    while (scoreList != NULL) {
        free(scoreList->score.name);
        ScoreList *temp = scoreList->next;
        free(scoreList);
        scoreList = temp;
    }
}

