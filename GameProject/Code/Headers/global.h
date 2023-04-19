#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "background.h"

#define SCREEN_W 1280
#define SCREEN_H 720

struct CELL_DATA_PILE{
    void* ptr;
    struct CELL_DATA_PILE *next;
};

struct SURFACE_CELL_PILE{
    SDL_Surface* surface;
    struct SURFACE_CELL_PILE* next;
};

struct FONT_CELL_PILE{
    TTF_Font* font;
    struct FONT_CELL_PILE *next;
};

typedef struct{
    SDL_Surface *surface;
    Image *background;
    Image *icon;
    short Fullscreen;
}Screen;


/* GLOBAL VARIABLES */
static struct CELL_DATA_PILE *PILE = NULL;
static struct SURFACE_CELL_PILE *SURFACE_PILE = NULL;
static struct FONT_CELL_PILE *FONT_PILE = NULL;




void* allocate(size_t size);

void add_to_pile(void* ptr);
void destroy_pile();


void add_to_surface_pile(SDL_Surface* ptr);
void destroy_surface_pile();

/*
* add_to_font_pile() is used to add fonts to the fonts pile queue in
* order to get destroyed in the end of program.
*/
void add_to_font_pile(TTF_Font* txt);

/*
* destroy_font_pile() is used to destroy the pile in the end of the
* program.
*/
void destroy_font_pile();

void DESTROY();

#endif