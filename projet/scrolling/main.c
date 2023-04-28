#include "source.h"

int main(){

FILE* fichier = NULL ; 
image bg1, bg2 , bg3 , bg4 , front, right, left , img , lightening ; 
texte txt1, txt2 ; 
SDL_Surface* monitor = NULL;
SDL_Event event ; 
Mix_Music  * rain ;  
Mix_Chunk * thunder ; 
int r = 0, l = 0 , u = 0  , a = 0 , b = 0 , v = 0 , scoreb  ; 
float x = 130 , xb = 0 , xu = 0 , xm = 5 , scorea = 0 ;  
char str[100],str1[20] ; 
fichier = fopen("meilleur_score","ab") ;

if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER )==-1){
	printf("Coundn't initialise\n");
}

	monitor = SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	//traitement.....
	
	// animation bg : 
	initilize_bg(&bg1,"/home/jessy/Desktop/projet/scrolling/animations_bg/bg1.bmp") ; 
	initilize_bg(&bg2,"/home/jessy/Desktop/projet/scrolling/animations_bg/bg2.bmp") ; 
	initilize_bg(&bg3,"/home/jessy/Desktop/projet/scrolling/animations_bg/bg3.bmp") ; 
	
	// animation charactere : 
	initilize_png(&right,"/home/jessy/Desktop/projet/scrolling/right.png",50,150) ;
	initilize_png(&left,"/home/jessy/Desktop/projet/scrolling/left.png",50,150) ; 
	initilize_png(&front,"/home/jessy/Desktop/projet/scrolling/front.png",50,150) ;
	 
	 // sound : 
	initialiser_music(rain) ;
	init_shunk(thunder,25) ; 
	
	//score : 
	initialiser_text(&txt1,"/home/jessy/Desktop/projet/scrolling/firasanscompressed-extralightitalic.otf",40,255,255,255,100,0) ;
	initialiser_text(&txt2,"/home/jessy/Desktop/projet/scrolling/FiraSans-BoldItalic.otf",30,255,255,255,0,5) ;
	
 	

while(event.type != SDL_QUIT){ 	

	scorea += 0.001 ; 
	sprintf(str,"%d",(int)scorea) ; 
	strcpy(str1,"Score : ") ; 
	
	afficher_text(monitor,txt1,str) ;
	afficher_text(monitor,txt2,str1) ;
	
	a++ ; 
	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
	afficher_image(front,monitor ,x,203) ; 
	
	
	
	b++ ; 
	if (v == 0 || b == 100000){ 
		v = 25 ; 
		musiquebref(thunder,v) ; 
		b = 0 ; 
		}  
	 
	
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
		
			case SDL_KEYDOWN : 
				switch (event.key.keysym.sym) {
                    			case SDLK_d:
                    				r = 1 ; 
                    				break ; 
                    			case SDLK_q:
                    				l = 1 ; 
                    				break ; 
					case SDLK_SPACE: 
						u = 1 ; 
                    			}
                    			
                    		break ;
                    		
                    	case SDL_KEYUP :
                    		switch (event.key.keysym.sym) {
                    			case SDLK_d:
                    				r = 0 ; 
                    				break ; 
                    			case SDLK_q:
                    				l = 0 ; 
                    				break ; 
                    			case SDLK_SPACE : 
                    				 u = 0 ; 
                    			} 
                    		break ; 
                    		
                    		
                    		} 
        		}
        	
		
		
 		
        if (r) {
        	   if (x < 420) {
	   		xb -= 0.04 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
			x += 0.01 ; 
			
			afficher_image(right,monitor ,x,203) ;
        		}
        		
        	   else {
        	   	if (xb >= -1699.032104){
				xb -= 0.05 ; 
				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
				afficher_image(right,monitor ,x,203) ;
        			}
        		else {
        			if (x<545){
        				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
        				x += 0.05 ; 
        				afficher_image(right,monitor ,x,203) ;
        			}	
        		
        		}
        	}	
        }
        if (l) { 
        	if (x > 130 ) {
        		xb += 0.04 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
			x -= 0.01 ; 
			afficher_image(left,monitor ,x,203) ;
			
			}
		else {
			if (xb <= 2.799999) {
				xb += 0.05 ; 
				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
				afficher_image(left,monitor ,x,203) ;
        			}
        		else {
        			if (x>5){
        				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
        				x -= 0.05 ; 
        				afficher_image(left,monitor ,x,203) ;
        			}
        		}
   
        	}
        }
        
        
        if (u){
        	if (xu <= 66.049431) {
        	xu += 0.08 ; 
        	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
        	afficher_image(front,monitor ,x,203) ;
        		}
        	} 
        else {
        	if (xu >= -1.14987){ 
        	xu -= 0.1 ; 
        	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu ,xb, &a) ; 
        	afficher_image(front,monitor ,x,203) ; 
        	}
        }
       
       
	
	
	//printf("%d |",scorea) ; 
	SDL_Flip(monitor); 
	
	}
	scoreb = (int)scorea ; 
	if (fichier != NULL){ 
		fwrite(&scoreb,4,1,fichier) ; 	
		fclose(fichier) ;
	}
	
	else 
		printf("Warning") ; 
		
	free_image(bg1); 
	free_image(bg2); 
	free_image(bg3); 
	free_image(right);
	free_image(left); 
	free_image(front);   
	free_text(txt1) ; 
	free_text(txt2) ; 
	liberer_musiquebref(thunder) ; 
	liberer_music(rain) ; 
	SDL_Quit() ;
	
	
    	return 0 ; 
}

