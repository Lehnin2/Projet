#ifndef MENU_H
#define MENU_H

#include "Images.h"
#include "Text.h"
#include "global.h"

struct MENU;

struct Button{
    Image *frames[2];
    Uint8 current;
    SDL_Rect position;
};

typedef struct Button Button;

struct BUTTON_CELL_PILE{
    Button* btn;
    struct BUTTON_CELL_PILE* next;
};

struct MENU{
    char title[20];
    Button *btn;
    struct MENU *children[5];
    struct MENU *parent;
    short nb_buttons;
};


/* GLOBAL VARIABLES */
static struct BUTTON_CELL_PILE *BUTTON_PILE = NULL;
static struct MENU *MENU_HOME = NULL;

/*  ======================================================= 
        =======================================================
        ======================================================= 
        =======================================================
        ======================================================= 
        =======================================================
        ======================================================= 
        =======================================================
        ======================================================= 
        =======================================================         FUNCTIONS BELOW !!!
        ======================================================= 
        =======================================================
        ======================================================= 
        =======================================================
        ======================================================= 
        =======================================================
        ======================================================= 
            ======================================================= 
*/

struct MENU* gen_menu();
void set_position(struct MENU* p);

/*
* make_button() calls load_Button_Frames() with text. 
*/
Button* make_button(char* title);

/*
* inside_btn() returns 1 if the cursor is inside the button, else 0.
*/
//int inside_btn(SDL_Event event, Button *btn);

/*
* blit_button() is used to print the button on a given surface.
*/
void blit_button(Button* btn, SDL_Surface* screen, short version);

/*
*
*/
void show_menu(struct MENU* active_menu, Screen *screen, SDL_Event event, short displayed, int y);
void print_children(struct MENU* p, int active);

#endif