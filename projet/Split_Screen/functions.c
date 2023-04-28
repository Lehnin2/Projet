#include "source.h"
void initilize_bg(image * bg,char * path){
	bg->front=SDL_LoadBMP(path);
	if(bg->front == NULL){
		printf("Pas d'image\n");
	}
	else{
		bg->pos.x=0;
		bg->pos.y=0;
	}
}

void initilize_png(image * img ,char * path,int x,int y){
	img->front=IMG_Load(path);
	if(img->front==NULL){
		printf("Pas d'image\n");
	}
	else{
		img->pos.x=x;
		img->pos.y=y;
	}
}

void afficher_bg(image img, SDL_Surface * screen , int x , int y ){

	img.pos.x = x ; 
	img.pos.y = y ;  
	SDL_BlitSurface(img.front,NULL,screen,&img.pos);
	
}

void afficher_image(image img, SDL_Surface * screen , int x , int y ){
	
	img.pos.x = x ; 
	img.pos.y = y ; 
	SDL_BlitSurface(img.front,NULL,screen,&img.pos);
	
}
void free_image(image img){
	SDL_FreeSurface(img.front);
}


void affichage_bg_animation(image bg1 , image bg2 , image bg3 , SDL_Surface * monitor , int xu , int xb, int * a ) {
	
		if (*a == 500 ){ 	
			afficher_bg(bg1,monitor,xb,xu) ;
			}
		  
		if (*a == 1000) {
			afficher_bg(bg2,monitor,xb,xu) ;
		}
			  
		if (*a == 1500){
			afficher_bg(bg3,monitor,xb,xu) ;
			
			*a = 0 ; 
			} 
}


void init_shunk(Mix_Chunk * music,int volume) {
	
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
}

void musiquebref(Mix_Chunk * music,int volume){ 

	music=Mix_LoadWAV("/home/jessy/Desktop/projet/scrolling/thunder.wav");
	if(music==NULL){
		printf("Couldn't load the sound\n");
	} 
	else {
		Mix_PlayChannel(-1,music,0);
		Mix_VolumeChunk(music,volume);
	}
}


void liberer_musiquebref(Mix_Chunk *music){//segmentation fault
	Mix_FreeChunk(music);
}



void initialiser_music(Mix_Music *music){
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) == -1 ) {
		printf("warning" ) ; 
	}
	music=Mix_LoadMUS("/home/jessy/Desktop/projet/scrolling/rain.mp3");
	Mix_PlayMusic(music,-1);
	Mix_VolumeMusic(700);
}

void liberer_music(Mix_Music *music){
	Mix_FreeMusic(music);
}

void initialiser_text(texte* text,char* font,float size,int r,int g,int b , int x , int y ){
	TTF_Init() ; 
	text->font=TTF_OpenFont(font,size);
	text->color.r=r;
	text->color.g=g;
	text->color.b=b;
	
	text->pos.x=x;
	text->pos.y=y;
	
}

void afficher_text(SDL_Surface* screen,texte text,char* message){
	
	
	text.txt=TTF_RenderText_Blended(text.font,message,text.color);
	
	SDL_BlitSurface(text.txt,NULL,screen,&text.pos);
	
}

void free_text(texte text){
	TTF_CloseFont(text.font); //segmentation fault
}

