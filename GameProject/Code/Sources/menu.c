#include "../Headers/Menu.h"
#include "../Headers/global.h"

void empty_string(char* str, int n){
    int i =0;
    for (i=0;i!=n;i++)
        str[i] = 0;
}

void make_parent(struct MENU** p, char* title, struct MENU* parent){
    *p = (struct MENU*)allocate(sizeof(struct MENU));
    strcpy((*p)->title, title);
    (*p)->btn = make_button(title);
    (*p)->parent = parent;
    (*p)->nb_buttons = 0;
    int i =0;
    for (i=0;i!=5;i++)
        (*p)->children[i] = NULL;
}

int append(struct MENU* matrix, int n, char *title){
    /* VARIABLES */
        int i=0;

    if (matrix){
        for (i=0;i!=n && matrix->children[i];i++);
        if (i < n){
            make_parent(&matrix->children[i], title, matrix);
            matrix->nb_buttons++;
        }
        else{
            printf("NOT ENOUGH SPACE\n");
            return -1;
        }
    }
    else printf("PARENT IS NULL\n");
    
    return i;
}

struct MENU* gen_menu(void){
    /* VARIABLES */
        int i=0, j=0, brackets = 0;
        struct MENU* active_parent = NULL;
        char 
            *LIST = "{PLAY,SETTINGS{LANGUAGE{FR,ENG},AUDIO{SFX,MUSIC},CONTROLS{CONTROLS},DISPLAY{WINDOWED,FULLSCREEN}},EXIT}",
            buffer[strlen(LIST)+1];
            
    /* CHECK THE VALIDITY OF THE LIST */
        empty_string(buffer, strlen(LIST)+1);
        for(i=0;i!=strlen(LIST);i++)
            if (LIST[i] == '{')
                brackets++;
            else if (LIST[i] == '}')
                brackets--;
            else if (LIST[i] == ',' || LIST[i] >='a' && LIST[i] <= 'z' || LIST[i] >='A' && LIST[i] <= 'Z')
                continue;
            else
                break;

        if (i<strlen(LIST)){
            printf("INVALID CHARACTER '%c' IN POSITION %d!\n",LIST[i],i);
            return NULL;
        }
        if (brackets == 0);
        else{
            if (brackets > 0)
                printf("MISSING %d \"BEGIN\" BRACKET(S) IN BUTTONS LIST!\n",brackets);
            else
                printf("MISSING %d \"END\" BRACKET(S) IN BUTTONS LIST!\n",abs(brackets));
            printf("MENU NOT GENERATED!\n");
            return NULL;
        }
        // IF VALID INIT THE HEAD OF THE MENU:
            make_parent(&MENU_HOME, "HOME", NULL);
            //MENU_HOME->title = "HOME";
            active_parent = MENU_HOME;
        

    /* GENERATE THE MENU */
        empty_string(buffer, strlen(LIST)+1);
        i = 0; j = 0;
        for(i=0;i!=strlen(LIST);i++){
            switch(LIST[i]){
                /* Define '{' function */
                case '{':
                    if (strlen(buffer))
                        active_parent = active_parent->children[append(active_parent, 5, buffer)];
                    empty_string(buffer, strlen(LIST)+1);
                    j=0;
                    break;

                /* Define ',' function */
                case ',':
                    if (strlen(buffer))
                        append(active_parent, 5, buffer);
                    empty_string(buffer, strlen(LIST)+1);
                    j=0;
                    break;

                /* Define '}' function */
                case '}':
                    if (strlen(buffer))
                        append(active_parent, 5, buffer);
                    active_parent = active_parent->parent;
                    empty_string(buffer, strlen(LIST)+1);
                    j=0;
                    break;

                /* Define 'Alpha' function */
                default:
                    buffer[j] = LIST[i];
                    j++;
                    break;
            }
        }
        // Import the Menu frame and set the buttons positions:
        menu_frame = load_image("../Images/Menu/Menu/menu_frame.png");
        menu_frame->position.x = (SCREEN_W-menu_frame->position.w)/2;
        menu_frame->position.y = (SCREEN_H-menu_frame->position.h)/2;
        set_position(MENU_HOME);

        if (MENU_HOME)
            return MENU_HOME;
}

void set_position(struct MENU* p){
    int i = 0, x = 0, y = 0;
    if (p->nb_buttons){
        y = menu_frame->position.h - (p->children[0]->btn->position.h)*p->nb_buttons;
        y /= (p->nb_buttons+1);
        x = (menu_frame->position.w-(p->children[0]->btn->position.w))/2;
        for(i=0;i!=p->nb_buttons;i++){
            p->children[i]->btn->position.y = y * (i+1) + p->children[i]->btn->position.h * i + menu_frame->position.y;
            p->children[i]->btn->position.x = x + menu_frame->position.x;
            set_position(p->children[i]);
        }
    }
}

int set_function(struct MENU* p, Screen* screen){
    if (!p->nb_buttons){
        if (!strcmp(p->title,"PLAY")){
            return 1;
        }
        else if (!strcmp(p->title,"WINDOWED") && screen->Fullscreen){
            SDL_UnlockSurface(screen->surface);
            SDL_WM_ToggleFullScreen(screen->surface);
            screen->Fullscreen = 0;
            return 1;
        }
        else if (!strcmp(p->title,"FULLSCREEN") && !screen->Fullscreen){
            SDL_WM_ToggleFullScreen(screen->surface);
            screen->Fullscreen = 1;
            return 1;
        }
        else if (!strcmp(p->title,"SFX")){
            return 1;
        }
        else if (!strcmp(p->title,"MUSIC")){
            return 1;
        }
        else if (!strcmp(p->title,"EXIT")){
            return 0;
        }
    }
}

int get_dimension(struct MENU* p){
    if (!p->parent)
        return 1;
    else
        return get_dimension(p->parent)+1;
}

void print_children(struct MENU* p, int active){
    if (p){
        if (!active)
            printf("%dD: %s\n", get_dimension(p), p->title);
        if (p->children[active]){
            print_children(p->children[active], 0);
            print_children(p, active+1);
        }
    }
    else
        printf("END OF ROAD!\n");
}

void show_menu(struct MENU* active_menu, Screen *screen, SDL_Event event, short displayed, int y){
    /* VARIABLES */
        short i, mouse;
        int btn_h;

    if (active_menu && active_menu->nb_buttons && SDL_WaitEvent(&event)){
        btn_h = active_menu->children[0]->btn->position.h + y;
        /* PRINT THE MENU ON THE SCREEN */
            // CHECK IF THE MENU IS ALREADY ON THE SCREEN:
                SDL_BlitSurface(menu_frame->surface, NULL, screen->surface, &menu_frame->position);
                for (i=0;i!=active_menu->nb_buttons;i++)
                    blit_button(active_menu->children[i]->btn, screen->surface, 0);
                if (!displayed){
                    y = active_menu->children[0]->btn->position.y - menu_frame->position.y;
                }

        /* THE NAVIGATION */
            if (event.motion.x >= active_menu->children[0]->btn->position.x && event.motion.x <= active_menu->children[0]->btn->position.x + active_menu->children[0]->btn->position.w){
                mouse = event.motion.y - menu_frame->position.y;
                i = mouse%btn_h;
                mouse /= btn_h;
                if (i >= y){
                    blit_button(active_menu->children[mouse]->btn, screen->surface, 1);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        if (active_menu->children[mouse]->nb_buttons)
                            show_menu(active_menu->children[mouse], screen, event, 0, 0);
                        else if (!set_function(active_menu->children[mouse], screen))
                            return;
                }
            }
            SDL_Flip(screen->surface);
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
                return;
            show_menu(active_menu, screen, event, 1, y);
    }
}

Button* make_button(char* title){
    /* VARIABLES */
        Button *btn = (Button*)allocate(sizeof(Button));
        SDL_Color color_not_selected = {255,0,0},
                color_selected = {255,255,255};     
        Text *t;

    // Set the default frame as "Not Selected":
    btn->current = 0;

    /* SELECTED BUTTON DISPLAY */
        // Download the image:
        btn->frames[1] = load_image("../Images/Menu/Menu/selected.png");
        // Load the text:
        t = Text_Create(title,"../Fonts/Technopollas.otf", color_selected, 14);
        // Set the text's position in the middle of the frame:
        t->position.x = (btn->frames[1]->surface->w - t->surface->w)/2;
        t->position.y = (btn->frames[1]->surface->h - t->surface->h)/2;
        // Print the text on the frame and then update the frame to get the button in order to return it:
        SDL_BlitSurface(t->surface, NULL, btn->frames[1]->surface, &t->position);
        SDL_Flip(btn->frames[1]->surface);

    /* NOT SELECTED BUTTON DISPLAY */
        // Download the image:
        btn->frames[0] = load_image("../Images/Menu/Menu/selected.png");
        // Load the text:
        t = Text_Create(title,"../Fonts/Technopollas.otf", color_not_selected, 14);
        // Set the text's position in the middle of the frame:
        t->position.x = (btn->frames[0]->surface->w - t->surface->w)/2;
        t->position.y = (btn->frames[0]->surface->h - t->surface->h)/2;
        // Print the text on the frame and then update the frame to get the button in order to return it:
        SDL_BlitSurface(t->surface, NULL, btn->frames[0]->surface, &t->position);
        SDL_Flip(btn->frames[0]->surface);

    // Set the position of the button:
    btn->position = btn->frames[0]->position;

    return btn;
}

/*
* inside_btn() returns an index, of a given array length, to the selected button,
* and if none is selected it returns -1.
*/
int inside_btn(SDL_Event event, int nb){
    /* VARIABLES */
        int n = -1, x, y;
    
    // Define the vulnerable zones:
        y = menu_frame->position.h/(nb+1);
        //x = (menu_frame->position.w-(p->children[0]->btn->position.w))/2;
    
    return n;
}

void blit_button(Button* btn, SDL_Surface* screen, short version){
    SDL_BlitSurface(btn->frames[version]->surface, NULL, screen, &btn->position);
}