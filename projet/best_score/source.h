#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#define SCREEN_W 501
#define SCREEN_H 501

typedef struct{
	SDL_Rect pos ;
	SDL_Surface * front ; 
}image;

typedef struct{
	SDL_Surface *txt;
	SDL_Rect pos;
	SDL_Color color;
	TTF_Font *font;
}texte;

void initilize_bg(image * bg,char * path ) ; 
void afficher_bg(image img, SDL_Surface * screen , int x, int y ) ; 
void initilize_png(image * img,char * path,int x,int y) ;
void afficher_image(image img , SDL_Surface * screen, int x , int y ) ; 
void free_image(image img) ; 
void initialiser_text(texte* text,char* font,float size,int r,int g,int b,int x,int y);
void afficher_text(SDL_Surface* screen,texte text,char* message);
void free_text(texte text);
void sort_f(char * nom_fich,int * n) ; 
	
