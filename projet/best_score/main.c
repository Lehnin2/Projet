#include "source.h"

int main() {

FILE* fichier = NULL ; 
image bg , button, score ; 
SDL_Surface* monitor = NULL;
SDL_Event event ; 
texte txt1,txt2,txt3 ; 
char str[20] ; 
int i,x,n,t[4] ; 

//traitement de fichier : 

fichier = fopen("/home/jessy/Desktop/projet/scrolling/replace","rb") ;
sort_f("/home/jessy/Desktop/projet/scrolling/meilleur_score",&n) ;  

if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1){
	printf("Coundn't initialise\n");
}

	monitor = SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	//traitement.....
	initilize_bg(&bg,"bg2.bmp") ; 
	initilize_png(&button,"/home/jessy/Desktop/projet/best_score/button.png",0,0) ; 
	initilize_png(&score,"/home/jessy/Desktop/projet/best_score/score.png",0,0) ; 
	
	
	initialiser_text(&txt1,"FreeSans.ttf",20,0,0,0,232,210) ;
	initialiser_text(&txt2,"FreeSans.ttf",20,0,0,0,232,283) ; 
	initialiser_text(&txt3,"FreeSans.ttf",20,0,0,0,232,350) ;  
	
	
	
	
	
 	afficher_bg(bg,monitor,0,0) ;
	afficher_image(button,monitor ,160,160) ;

while(event.type != SDL_QUIT){ 	
	
	while(SDL_PollEvent(&event)){
		
		switch(event.type){
			
			case SDL_MOUSEBUTTONUP:
				
				if (event.button.button == SDL_BUTTON_LEFT &&
					event.button.x >= 184 && event.button.x <= 313 &&
					event.button.y >= 228 && event.button.y <= 267) {
						afficher_image(score,monitor ,-5,-5) ; 
						
						
						if (fichier != NULL){
							/*fread(&x,sizeof(int),1,fichier)  ; 
							sprintf(str,"%d ",x) ;
							afficher_text(monitor,txt1,str) ; 
							*/
							i = 0 ; 
							while(!feof(fichier) && i != 4){
								fread(&x,sizeof(int),1,fichier)  ; 
								t[i] = x ; 
								i++ ; 
							} 
							if (i == 2 ) {
								sprintf(str,"%d ",t[0]) ;
								afficher_text(monitor,txt1,str) ;
							}
							if (i == 3 ) {
								sprintf(str,"%d ",t[0]) ;
								afficher_text(monitor,txt1,str) ;
								sprintf(str,"%d ",t[1]) ;
								afficher_text(monitor,txt2,str) ;
								}
							if (i > 3 ) {
								sprintf(str,"%d ",t[2]) ;
								afficher_text(monitor,txt3,str) ; 
		            					sprintf(str,"%d ",t[0]) ;
								afficher_text(monitor,txt1,str) ;
								sprintf(str,"%d ",t[1]) ;
								afficher_text(monitor,txt2,str) ;
                    					} 
                    				}
                    				else 
                    					printf("Warning ! ") ; 
                    		} 
                    		break; 
        		}
        	}
	SDL_Flip(monitor); 
	
	}	
	
	fclose(fichier) ;
	free_image(bg); 
	free_image(button);  
	free_image(score);
	free_text(txt1);
	free_text(txt2);
	free_text(txt3);
	SDL_Quit() ;
	
	
    	return 0 ; 
	
}

