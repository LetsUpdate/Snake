//
// Created by János Tánczos on 2021. 11. 18..
//
#include "save_system.h"


bool SaveSnake(Snake * snake){
    FILE* file = fopen(SNAKE_DATA_FILE,"w");
    //error handling
    if(file==NULL){
        perror("Nem sikerült megnyitni a SNAKE_DATA fájlt");
        return false;
    }
    // writing to file
    while (snake!=NULL){
        fprintf(file,"%d,%d/",snake->bodyPart.x,snake->bodyPart.y);
        snake = snake->next;
    }
    //close
    fprintf(file,"\n");
    fclose(file);

}

Snake * loadSnake(){
    FILE * file = fopen(SNAKE_DATA_FILE,"r");
    if(file==NULL){
        return NULL;
    }

    //The save is not valid anymore so...
    remove(SNAKE_DATA_FILE);
}


