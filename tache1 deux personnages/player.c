#include "player.h"

/*#define Ground 350
#define VITESSE 5
#define MAX_VITESSE 10
#define MAX_JUMP_VITESSE 25
*/
int nbtab = 10,Ground=318;

void filltable(SDL_Rect *crop)
{
    int i;
    
    //idle droite
    crop[0].x = 0; 
    crop[0].y = 0;

    crop[0].w = 37;
    crop[0].h = 42;

    for (i = 1; i < nbtab; i++)
    {
        crop[i].w = 37;
        crop[i].h = 42;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 0;
    }

    //idle gauche
    crop[10].x = 0;
    crop[10].y = 42;

    crop[10].w = 37;
    crop[10].h = 42;

    for (i = 11; i < 2 * nbtab; i++)
    {
        crop[i].w = 37;
        crop[i].h = 42;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 42;
    }

    //courir a droite
    crop[20].x = 0;
    crop[20].y = 84;

    crop[20].w = 43;
    crop[20].h = 44;

    for (i = 21; i < 3 * nbtab; i++)
    {
        crop[i].w = 43;
        crop[i].h = 44;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 84;
    }

    //courir a gauche
    crop[30].x = 0;
    crop[30].y = 128;

    crop[30].w = 43;
    crop[30].h = 44;

    for (i = 31; i < 4 * nbtab; i++)
    {
        crop[i].w = 43;
        crop[i].h = 44;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 128;
    }

    //saut a droite
    crop[40].x = 0;
    crop[40].y = 172;

    crop[40].w = 43;
    crop[40].h = 44;

    for (i = 41; i < 5 * nbtab; i++)
    {
        crop[i].w = 43;
        crop[i].h = 44;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 172;
    }

    //saut a gauche
    crop[50].x = 0;
    crop[50].y = 216;

    crop[50].w = 43;
    crop[50].h = 44;

    for (i = 51; i <6 * nbtab; i++){

      crop[i].w = 43;
      crop[i].h = 44;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 216;
    }
}

void init_Perso(Perso *p,char *ch[], int nbp)
{
    p->vie.vie = IMG_Load("vie.png");
    p->sprite = IMG_Load(*ch);

    p->n = 0;
    p->currentMode = 0;
    p->score=100;
    p->PersoPos.x = 0;
    p->PersoPos.y = Ground;

    p->acceleration = 5;
    p->vitesse = 5;

    p->xStep = 3;
    p->yStep = 3;
    p->i.left = 0;
    p->i.right = 0;

    p->i.space = 0;
    //p->direction = 0;

    filltable(p->rects);

   if(nbp==1)
{
    (p->vie).posvie.x=0;
} 
   if(nbp==2)
{
	(p->vie).posvie.x=350;
}
    (p->vie).posvie.y=0;
    (p->vie).posvie.w=25;
    (p->vie).posvie.h=14;
     


}

void afficher_Perso(Perso *p, SDL_Surface *screen, SDL_Surface *bg)
{
    SDL_BlitSurface(p->sprite, &p->rects[p->n], screen, &p->PersoPos);
    SDL_BlitSurface(p->vie.vie, NULL, bg, &(p->vie).posvie);



}

void Animation(Perso *p)//debout a droite ou a guauche pour l'animation animation
{
    if (p->currentMode == 0) // debout a droite
    {
        if (p->n < 0 || p->n > 9)
        {
            p->n = 0;
        }
        p->n++;

        if (p->n > nbtab - 1)
        {
            p->n = 0;
        }
    }
    else if (p->currentMode == 1) // debout a guauche
    {

        if (p->n < 10 || p->n > 19)
        {
            p->n = 10;
        }
        p->n++;

        if (p->n > 19)
        {
            p->n = 10;
        }
    }
if (p->currentMode == 2)// courrir a droite
    {
        if (p->n < 20 || p->n > 29)
        {
            p->n = 20;
        }
        p->n++;
        if (p->n > 29)
        {
            p->n = 20;
        }
    }
    else if (p->currentMode == 3)// courrir a guauche
    {
        if (p->n < 30 || p->n > 39)
        {
            p->n = 30;
        }
        p->n++;
        if (p->n > 39)
        {
            p->n = 30;
        }
    }
}



void jumpAnimation(Perso *p, SDL_Surface *screen, SDL_Surface *bg, SDL_Rect bgPos, double *v_y) {
   //---------
double v_x = 0.01;

double v_saut = 4;
double v_grav = 1;


//---------------


if (p->i.space == 1)
    {
        if (p->i.right == 1)
        {
            p->currentMode = 4;

        }
        else if (p->i.left == 1)
        {
            p->currentMode = 5;

        }
    else
        {
       if (p->currentMode == 0)
            {
                p->currentMode = 4;

            }
            else if (p->currentMode == 1)
            {
                p->currentMode = 5;

            }
        }
    }
    
    if (p->currentMode == 4)
    {
             p->PersoPos.x += v_x/10;
             *v_y -= v_grav;
             p->PersoPos.y -= *v_y; 
             if(p->PersoPos.y>=Ground)
		{
			*v_y=8;
			p->PersoPos.y=Ground;
			p->i.space=0;
			p->currentMode =0;
			
		}
       
	
      
      SDL_BlitSurface(p->sprite, &p->rects[p->n], screen, &p->PersoPos);
      SDL_Flip(screen);
   SDL_Delay(10);
    }
    else if (p->currentMode == 5)
    {
      
    

             p->PersoPos.x += v_x/10;
             *v_y -= v_grav;
             p->PersoPos.y -= *v_y; 
             if(p->PersoPos.y>=Ground)
		{
			*v_y=8;
			p->PersoPos.y=Ground;
			p->i.space=0;
			p->currentMode =1;
			
		}


         
            SDL_BlitSurface(p->sprite, &p->rects[p->n], screen, &p->PersoPos);
            SDL_Flip(screen);
   SDL_Delay(10);
        
    }
}


void moveperso(Perso *p, Uint32 dt,int nbp)
{

        
/*                                  right                                            */        
        if (p->i.right == 1 )
        {

            p->PersoPos.x += p->xStep;
            if (p->acceleration <6)
		    {
		        p->acceleration += 0.2;
		    }

        /*if(p->PersoPos.x==350)/
		     {
		        p->acceleration == 0;
		        p->i.right == 0;
		        p->xStep=0;
		     } */
/*Fonction double joueur*/
          if(p->PersoPos.x>=175 && nbp==1)
		     {
		        p->PersoPos.x=175;
		     }

         if(p->PersoPos.x>=525 && nbp==2)
		     {
		        p->PersoPos.x=525;
		     }

         }

         
/*----------------------------------------------------------------------------------------------*/         
/*                                    left                                                       */
	if (p->i.left == 1)
        {

            p->PersoPos.x -= p->xStep;

            if (p->acceleration <6)
            {
                p->acceleration += 0.2;
		}
                if(p->PersoPos.x==0)
                    {
                       p->acceleration==0;
                    }

/*Fonction doubl joueur*/
         if(p->PersoPos.x<=350 && nbp==2)
		     {
		        p->PersoPos.x=350;
		     }
            }
        
/*-------------------------------------------------------------------------------------------------------*/


    if (p->i.right == 0 && p->i.left == 0)
    {
        p->acceleration = 0;
    }

p->xStep = 0.5 * p->acceleration * dt * dt + p->vitesse * dt;
}


