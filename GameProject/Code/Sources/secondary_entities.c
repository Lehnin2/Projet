#include "../Headers/secondary_entites.h"

void initEnnemi(Ennemi *e){
    /* VARIABLES */
        int w = 90, h = 98, i;

    /* SET THE FRAMES RIGHT */
        // Load the sprite sheet:
        e->sprite = load_image("../Images/Enemi/enemy.png");
        // Set the right standing frame:
        for (i=0;i!=3;i++){
            e->standing_right[i].x = i*w;
            e->standing_right[i].y = h*3;
            e->standing_right[i].h = h;
            e->standing_right[i].w = w;
        }
        // Set the left standing frame:
        for (i=0;i!=3;i++){
            e->standing_left[i].x = i*w;
            e->standing_left[i].y = h;
            e->standing_left[i].h = h;
            e->standing_left[i].w = w;
        }
        // Set the left walking frame:
        for (i=0;i!=10;i++){
            e->walking_left[i].x = i*w;
            e->walking_left[i].y = h*5;
            e->walking_left[i].h = h;
            e->walking_left[i].w = w;
        }
        // Set the right walking frame:
        for (i=0;i!=10;i++){
            e->walking_right[i].x = i*w;
            e->walking_right[i].y = h*7;
            e->walking_right[i].h = h;
            e->walking_right[i].w = w;
        }
    
    /* SET THE DEFAULT DIRECTION */
        e->direction = 0;
    /* SET THE DEFAULT FRAME */
        e->frame = e->standing_right;
        e->frame_number = 0;
    /* SET THE DEFAULT POSITION */
        e->pos.h = h;
        e->pos.w = w;
        e->pos.x = 0;
        e->pos.y = GROUND-h;
        e->moving = 0;
    /* SET THE DEFAULT SPEED PARAMETERS */
        e->travel_time = 10;
        e->steps = 0;
    /* RESET THE TIMERS */
        e->animation_timer = 0;
        e->movement_timer = 0;
}

void afficherEnnemi(Ennemi e, SDL_Surface *screen){
    /* VARIABLES */


    /* BLIT THE ENEMY ON THE SURFACE PASSED IN ARGS */
        SDL_BlitSurface(e.sprite->surface, e.frame+e.frame_number, screen, &e.pos);
}

void animerEnnemi(Ennemi *e){
    /* VARIABLES */
    
    /* UPDATE THE CURRENT FRAME */
    if (e->moving){
        if (e->direction)
            e->frame = e->walking_left;
        else
            e->frame = e->walking_right;
        e->frame_number = (e->frame_number+1)%10;
    }
    else{
        if (e->direction)
            e->frame = e->standing_left;
        else
            e->frame = e->standing_right;
        e->frame_number = (e->frame_number+1)%3;
    }
}

void move(Ennemi *e){
    /* VARIABLES */
        int distance = e->steps;

    /* SET THE MOVING-WAITING ALGORITHM */
        if (e->moving){
            if (e->movement_timer == 0 || (SDL_GetTicks()) >= e->movement_timer){
                // CHOOSE THE DISTANCE TO COVER:
                if (e->moving < e->steps || distance == 0)
                    distance = e->moving;
                // APPLY THE DISTANCE COVERED TO THE POSITION OF THE ENEMY:
                if (e->direction)
                    e->pos.x -= distance;
                else
                    e->pos.x += distance;
                // IF IT TOUCHES THE SCREEN THEN STOP AND GO TO THE OPPOSITE DIRECTION:
                if (e->pos.x >= SCREEN_W - e->pos.w){
                    e->pos.x = SCREEN_W - e->pos.w;
                    e->moving = 0;
                }
                else if (e->pos.x < 0){
                    e->pos.x = 0;
                    e->moving = 0;
                }
                // ELSE DECREASE THE DISTANCE COVERED:
                else
                    e->moving -= distance;
                // UPDATE THE TIMER:
                e->movement_timer = SDL_GetTicks() + e->travel_time;
            }
            // IF THE DISTANCE TO COVER IS NULL THEN GENERATE RANDOM WAITING TIME:
            if (!e->moving){
                e->movement_timer = SDL_GetTicks() + rand() % 1000;
                e->frame_number = 0;
            }
        }
        else{
            /* IF TIMER IS NULL THEN MOVE ELSE WAIT */
                if (!e->movement_timer){
                    // GENERATE RANDOM DISTANCE
                    srand(time(NULL));
                    e->moving = rand() % SCREEN_W;
                    // GENERATE RANDOM TIME
                    srand(time(NULL));
                    e->travel_time = (rand() % 19) +1;
                    // FLIP THE DIRECTION
                    e->direction++;
                    // RESET THE FRAME ANIMATION INDEX
                    e->frame_number = 0;
                    // SET THE NUMBER OF STEPS
                    distance = e->steps = (float)e->moving/(float)e->travel_time;
                }
                else if (SDL_GetTicks() >= e->movement_timer)
                    e->movement_timer = 0;
        }
    /* UPDATE THE CURRENT DISPLAY FRAME */
        // IF THE TIMER IS UP THEN UPDATE ELSE DON'T
            if (SDL_GetTicks() >= e->animation_timer){
                animerEnnemi(e);
                e->animation_timer = SDL_GetTicks() + e->travel_time;
            }
}

int collisionBB(SDL_Rect posp, SDL_Rect pose){
    /* VARIABLES */
}

void moveIA(Ennemi *e){
    /* VARIABLES */
}