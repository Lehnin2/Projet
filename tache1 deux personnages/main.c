#include "player.h"


int main()
{
Mix_Music *music;
Mix_Chunk *sound1[10],*sound3;



TTF_Init();
TTF_Font *police = NULL;
police = TTF_OpenFont("TIMES.ttf", 45);
SDL_Color couleur = {255, 255, 255};
char buffer[50];

SDL_Surface *scoreP;
SDL_Surface *scoreP2;

 SDL_Rect positionscore;
 positionscore.x=600;
 positionscore.y=0;

 SDL_Rect positionscore2;
 positionscore2.x=100;
 positionscore2.y=0;


    int done = 1,i,j=1,k,q=-1,vm=50,vsfx=100;
    
   
    char filename1[20];
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Surface *screen, *bg;

    screen = SDL_SetVideoMode(700, 406, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    music= Mix_LoadMUS("music/theme.mp3");
    Mix_VolumeMusic(vm);
    Mix_PlayMusic(music,-1);

for(k=0;k<10;k++){
        sprintf(filename1,"music/l%d.wav",k);
sound1[k]= Mix_LoadWAV(filename1);
}

sound3= Mix_LoadWAV("music/j1.wav");


    SDL_Rect bgPos;
    bgPos.x = 0;
    bgPos.y = 0;


    Perso p;
    char *ch="sprites/hero1 212.png";
    char *ch2="sprites/hero2 212.png";
    init_Perso(&p,&ch,1);

    Perso p2;
    init_Perso(&p2,&ch2,2);
    p2.PersoPos.x = 350;
    /*p2.vie.posvie.x=350;*/

	sprintf(buffer, "%d", p.score);
	scoreP = TTF_RenderText_Blended(police, buffer, couleur);
	
	sprintf(buffer, "%d", p2.score);
	scoreP2 = TTF_RenderText_Blended(police, buffer, couleur);

 

    Uint32 dt, t_prev;
	double	v_y=8;

    bg = IMG_Load("home.png");

    SDL_Flip(screen);

    SDL_Event event;



    while (done)
    {

         SDL_BlitSurface(bg, NULL, screen, &bgPos);
         t_prev = SDL_GetTicks();

         
	 
          


        //if (p.currentMode == 0 || p.currentMode == 2 && p2.currentMode == 0 || p2.currentMode == 2 )
        /* 0: idle droite
        1:idle gauche
        2:cours a droite
        3:cours a gauche
        4: saut a droite
 	5: saut a gauche
        */
      

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:

                done = 0;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = 0;
                    break;

                case SDLK_SPACE:
                    p.i.space = 1;//vrai
                          Mix_PlayChannel(1,sound3,0);
                    break;
                 case SDLK_z:
                    p2.i.space = 1;


                    break;

                case SDLK_RIGHT:
                    p.i.right = 1;
                    p.currentMode = 2;
                
                  

	          
                    break;

                case SDLK_d:
                    p2.i.right = 1;
                    p2.currentMode = 2;

                    break;

                case SDLK_LEFT:
                   p.i.left = 1;
                    p.currentMode = 3;
                  /*if(p.PersoPos.x>=175 )
		     {
		        p.acceleration == 0;
		        p.i.right == 0;
		        p.xStep=0;
			p.PersoPos.x==175;

		     }*/



                    break;
                case SDLK_q:
                   p2.i.left = 1;
                    p2.currentMode = 3;
                 break;


                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                   
                    if (p.i.right == 1)
                    {
                        p.currentMode = 2;
                    }
                    else if (p.i.left == 1)
                    {
                        p.currentMode = 3;
                    }
                    break;

                     case SDLK_z:
                    
                    if (p2.i.right == 1)
                    {
                        p2.currentMode = 2;
                    }
                    else if (p2.i.left == 1)
                    {
                        p2.currentMode = 3;
                    }

                    break;

                case SDLK_RIGHT:
                    p.i.right = 0;//faux
                    p.currentMode = 0;
                    break;

                case SDLK_d:
                    p2.i.right = 0;
                    p2.currentMode = 0;
                    break;

                case SDLK_LEFT:
                    p.i.left = 0;
                    p.currentMode = 1;


                    break;
                case SDLK_q:
                    p2.i.left = 0;
                    p2.currentMode = 1;
                    break;


                }
                break;
            }
           // dt = SDL_GetTicks() - t_prev;
            dt=2,2;
        }

        
        moveperso(&p, dt,1);
      
        moveperso(&p2, dt,2);

        

        SDL_BlitSurface(bg, NULL, screen, &bgPos);

        Animation(&p);
        jumpAnimation(&p, screen, bg, bgPos,&v_y);
        afficher_Perso(&p, screen,bg);

        Animation(&p2);
        jumpAnimation(&p2, screen, bg, bgPos,&v_y);
        afficher_Perso(&p2, screen,bg);
	SDL_BlitSurface(scoreP, NULL, screen, &positionscore);
	SDL_BlitSurface(scoreP, NULL, screen, &positionscore2);

        SDL_Flip(screen);
   SDL_Delay(50);
    }

    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}
