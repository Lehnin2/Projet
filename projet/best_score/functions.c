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

void sort_f(char * nom_fich,int * n){
	int i,x=-1,max,aux,j,l;
	int * t ; 
	FILE * fichier , * replace   ; 
	
	fichier = fopen(nom_fich,"r+b") ; 
	if (fichier != NULL ) {
	
		replace = fopen("/home/jessy/Desktop/projet/scrolling/replace","wb") ; 
		t = (int * )malloc(sizeof(int) * 1 ) ;
	
		while(!feof(fichier)) {
			x++; 
			t = (int*) realloc(t,sizeof(int)* (x+1) ) ;   
			fread(&l,sizeof(int),1,fichier); 
			t[x] = l ; 
			}
		
		// simple tri : 
		for (i = 0; i < x-1; i++) {
       			for (j = 0; j < x-i-1; j++) {
			    if (t[j] < t[j+1]) {
			    
				aux = t[j];
				t[j] = t[j+1];
				t[j+1] = aux;
				
			    }
			}
		    }
		    
		    
		    fwrite(t,sizeof(int),x,replace) ;  
		    
		    fclose(replace) ;  
		    fclose(fichier) ; 
		   
	}

} 

