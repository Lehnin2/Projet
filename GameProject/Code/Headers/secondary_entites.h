#ifndef SECONDARY_ENTITIES_H
#define SECONDARY_ENTITIES_H

#include "Images.h"
#include "background.h"
#include "global.h"
#include <time.h>

typedef struct{
    Image *sprite;
    SDL_Rect standing_right[3];
    SDL_Rect standing_left[3];
    SDL_Rect walking_right[10];
    SDL_Rect walking_left[10];
    SDL_Rect *frame;
    int frame_number;
    unsigned short direction:1; // 0=R 1=L
    SDL_Rect pos;
    int moving; // distance length
    int steps;  // (moving/travel_time)
    int travel_time; // time in milliseconds to complete a movement
    Uint32 movement_timer; // time taken to move or wait
    Uint32 animation_timer; // time taken to update the frames
}Ennemi;

/* GLBOAL VARIABLES */


void initEnnemi(Ennemi *e);
void afficherEnnemi(Ennemi e, SDL_Surface *screen);
void animerEnnemi(Ennemi *e);
void move(Ennemi *e);
int collisionBB(SDL_Rect posp, SDL_Rect pose);
void moveIA(Ennemi *e);

#endif