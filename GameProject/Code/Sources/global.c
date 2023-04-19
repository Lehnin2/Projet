#include "../Headers/global.h"

void* allocate(size_t size){
    /* VARIABLES */
        void* ptr = malloc(size);

    // Add variable to the pile of destruction:
    add_to_pile(ptr);
   
    return ptr;
}

void add_to_pile(void* ptr){
    /* VARIABLES */
    struct CELL_DATA_PILE *cell = (struct CELL_DATA_PILE*)malloc(sizeof(struct CELL_DATA_PILE));

    // Get the cell ready and add it to the pile:
    cell->next = PILE;
    cell->ptr = ptr;
    PILE = cell;
}

void destroy_pile(){
    /* VARIABLES */
    struct CELL_DATA_PILE *cell = PILE;

    // Loop to free the pile until it's empty (NULL)
    while(PILE){
        cell = PILE;
        PILE = cell->next;
        free(cell->ptr);
        free(cell);
    }
}

void add_to_font_pile(TTF_Font* txt){
    /* VARIABLES */
    struct FONT_CELL_PILE *new_cell = (struct FONT_CELL_PILE*)allocate(sizeof(struct FONT_CELL_PILE));

    // Add text to the cell and make it the first:
    new_cell->font = txt;
    new_cell->next = FONT_PILE;
    FONT_PILE = new_cell;
}


void destroy_font_pile(){
    /* VARIABLES */
    struct FONT_CELL_PILE *cell = FONT_PILE;

    // Loop for destroying the cells decreasingly in levels:
    while(FONT_PILE){
        cell = FONT_PILE;
        FONT_PILE = cell->next;
        TTF_CloseFont(cell->font);
    }
}

void add_to_surface_pile(SDL_Surface* ptr){
    /* VARIABLES */
    struct SURFACE_CELL_PILE *cell = (struct SURFACE_CELL_PILE*)allocate(sizeof(struct SURFACE_CELL_PILE));

    // Get the cell ready and add it to the pile:
    cell->next = SURFACE_PILE;
    cell->surface = ptr;
    SURFACE_PILE = cell;    
}

void destroy_surface_pile(){
    /* VARIABLES */
    struct SURFACE_CELL_PILE *cell = SURFACE_PILE;

    // Loop to free the pile until it's empty (NULL)
    while(SURFACE_PILE){
        cell = SURFACE_PILE;
        SURFACE_PILE = cell->next;
        SDL_FreeSurface(cell->surface);
    }
}

void DESTROY(){
    destroy_surface_pile();
    destroy_font_pile();
    destroy_pile();
}