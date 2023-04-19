#include "../Headers/GAME.h"

/* VARIABLES */
Screen *screen;
Button *btn1;
SDL_Event event;
SDL_Color color = {100,49,180};
short boucle = 1;
float frequency = 1000/30; // fps = 1000ms/real_fps

int main(){
    /* NECESSARY INITS */
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) == -1){
        printf("COULDN'T INITIALIZE SDL DUE TO THE FOLLOWING ERROR: %s\n",SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1){
        printf("COULDN'T INITIALIZE SDL DUE TO THE FOLLOWING ERROR: %s\n",SDL_GetError());
        return 1;
    }
    
    /* PREPARE THE SCREEN */
        screen = (Screen*)allocate(sizeof(Screen));
        // Load the background:
        screen->background = load_image("../Images/Menu/Background/back.png");
        
        // Set the screen:
        screen->icon = load_image("../Images/Icons/icon.png");
        SDL_WM_SetIcon(screen->icon->surface, NULL);
        SDL_WM_SetCaption("KARMA", NULL);
        screen->surface = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 0, SDL_DOUBLEBUF|SDL_HWSURFACE);
        screen->Fullscreen = 0;
        
    /* GENERATE THE MENU */
        MENU_HOME = gen_menu();
        
    /* GAME LOOP */
    while(boucle){
        // Set the display:
            SDL_BlitSurface(screen->background->surface, NULL, screen->surface, &screen->background->position);
        /* THE MENU */
            show_menu(MENU_HOME, screen, event, 0, 0);
            break;
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                boucle = 0;
        }
        SDL_Delay(frequency);
    }

    
    /* FREEING THE ALLOCATED MEMORY */
        SDL_FreeSurface(screen->surface);
        DESTROY();
        TTF_Quit();
        SDL_Quit();
    
    printf("EXIT SUCCEEDED!\n");
    
    return 0;
}
