#ifndef player_H_INCLUDED
#define player_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
typedef struct {
  SDL_Surface *vie;
  SDL_Rect posvie;

} Vie;

typedef struct
{
    int left, right, space;
   
} input;
typedef struct
{
    SDL_Surface *sprite;
    SDL_Rect PersoPos;//xwdh
    SDL_Rect rects[100];

    int n;// case de la matrice
    float xStep, yStep;
    double acceleration, vitesse;
    int currentMode;
    input i;
    //int direction ; //int direction
    Vie vie;
    int score;

    
} Perso;

void filltable(SDL_Rect *crop);
void init_Perso(Perso *p,char *ch[100], int nbp);
void afficher_Perso(Perso *p, SDL_Surface *screen, SDL_Surface *bg);
void Animation(Perso *p);
void jumpAnimation(Perso *p, SDL_Surface *screen, SDL_Surface *bg, SDL_Rect bgPos,double *v_y);
void moveperso(Perso *p, Uint32 dt, int nbp);

#endif
