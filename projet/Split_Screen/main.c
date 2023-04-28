#include "source.h"

int main(){

FILE* fichier = NULL ; 
image bg1, bg2 , bg3 , front, right, left , img , splitline; 
texte txt1, txt2 ; 
SDL_Surface* monitor = NULL;
SDL_Event event ; 
Mix_Music  * rain ;  
Mix_Chunk * thunder ; 

int r1 = 0, l1 = 0 , u1 = 0 , r2 = 0 , l2 = 0 , u2 = 0 , a1 = 0 , a2 = 0 , b = 0 , v = 0 , scoreb  ; 

float x1 = 130 , x2 = 130 , xb1 = 0 , xu1 = 0 , xb2 = 0 , xu2 = 288 , xm = 5 , scorea = 0 ;  

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
	 
	//split_screen 
	initilize_png(&splitline,"/home/jessy/Desktop/projet/Split_Screen/splitline.png",0,288) ;
	
	// sound : 
	initialiser_music(rain) ;
	init_shunk(thunder,25) ; 
	
	//score : 
	initialiser_text(&txt1,"/home/jessy/Desktop/projet/scrolling/firasanscompressed-extralightitalic.otf",40,255,255,255,100,0) ;
	initialiser_text(&txt2,"/home/jessy/Desktop/projet/scrolling/FiraSans-BoldItalic.otf",30,255,255,255,0,5) ;
	
 	afficher_image(splitline,monitor ,0,240) ; 

while(event.type != SDL_QUIT){ 	

	scorea += 0.001 ; 
	sprintf(str,"%d",(int)scorea) ; 
	strcpy(str1,"Score : ") ; 
	
	afficher_text(monitor,txt1,str) ;
	afficher_text(monitor,txt2,str1) ;
	
	a1++ ; 
	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ;
	 
	a2++ ; 
	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ;
	
	afficher_image(front,monitor ,x1,203) ; 
	
	afficher_image(front,monitor ,x2,490) ; 
	
	
	
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
                    				r1 = 1 ; 
                    				break ; 
                    			case SDLK_q:
                    				l1 = 1 ; 
                    				break ; 
					case SDLK_z: 
						u1 = 1 ; 
						break ; 
					case SDLK_RIGHT:
                    				r2 = 1 ; 
                    				break ; 
                    			case SDLK_LEFT:
                    				l2 = 1 ; 
                    				break ; 
					case SDLK_UP: 
						u2 = 1 ; 
                    			}
                    			
                    		break ;
                    		
                    	case SDL_KEYUP :
                    		switch (event.key.keysym.sym) {
                    			case SDLK_d:
                    				r1 = 0 ; 
                    				break ; 
                    			case SDLK_q:
                    				l1 = 0 ; 
                    				break ; 
                    			case SDLK_z : 
                    				u1 = 0 ; 
                    				break ; 
                    			case SDLK_RIGHT:
                    				r2 = 0 ; 
                    				break ; 
                    			case SDLK_LEFT:
                    				l2 = 0 ; 
                    				break ; 
                    			case SDLK_UP : 
                    				u2 = 0 ;  
                    			} 
                    		break ; 
                    		
                    		
                    		} 
        		}
        	
		
		
 		
        if (r1) {
        	   if (x1 < 420) {
	   		xb1 -= 0.04 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
			x1 += 0.01 ; 
			
			afficher_image(right,monitor ,x1,203) ;
        		}
        		
        	   else {
        	   	if (xb1 >= -1699.032104){
				xb1 -= 0.05 ; 
				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
				afficher_image(right,monitor ,x1,203) ;
        			}
        		else {
        			if (x1<545){
        				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
        				x1 += 0.05 ; 
        				afficher_image(right,monitor ,x1,203) ;
        			}	
        		
        		}
        	}	
        }
        if (l1) { 
        	if (x1 > 130 ) {
        		xb1 += 0.04 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
			x1 -= 0.01 ; 
			afficher_image(left,monitor ,x1,203) ;
			
			}
		else {
			if (xb1 <= 2.799999) {
				xb1 += 0.05 ; 
				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
				afficher_image(left,monitor ,x1,203) ;
        			}
        		else {
        			if (x1 >5){
        				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
        				x1 -= 0.05 ; 
        				afficher_image(left,monitor ,x1,203) ;
        			}
        		}
   
        	}
        }
        
        
        if (u1){
        	if (xu1 <= 66.049431) {
        	xu1 += 0.08 ; 
        	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
        	afficher_image(front,monitor ,x1,203) ;
        		}
        	} 
        else {
        	if (xu1 >= -1.14987){ 
        	xu1 -= 0.1 ; 
        	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu1 ,xb1, &a1) ; 
        	afficher_image(front,monitor ,x1,203) ; 
        	}
        }
       
       // split_screen : 
      
       
       if (r2) {
        	   if (x2 < 420) {
	   		xb2 -= 0.04 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
			x2 += 0.01 ; 
			
			afficher_image(right,monitor ,x2,490) ;
        		}
        		
        	   else {
        	   	if (xb2 >= -1699.032104){
				xb2 -= 0.05 ; 
				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
				afficher_image(right,monitor ,x2,490) ;
        			}
        		else {
        			if (x2<545){
        				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
        				x2 += 0.05 ; 
        				afficher_image(right,monitor ,x2,490) ;
        			}	
        		
        		}
        	}	
        }
        
        
        if (l2) { 
        	if (x2 > 130 ) {
        		xb2 += 0.04 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
			x2 -= 0.01 ; 
			afficher_image(left,monitor ,x2,490) ;
			
			}
		else {
			if (xb2 <= 2.799999) {
				xb2 += 0.05 ; 
				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
				afficher_image(left,monitor ,x2,490) ;
        			}
        		else {
        			if (x2>5){
        				affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
        				x2 -= 0.05 ; 
        				afficher_image(left,monitor ,x2,490) ;
        			}
        		}
   
        	}
        }
        
       /*
        if (u2){ 
        	if (xu2 <= 66.049431) {
			xu2 += 0.08 ; 
			affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
			afficher_image(front,monitor ,x2,490) ;
        		}
        	} 
        else {
        	if (xu2 >= -1.14987){ 
        	xu2 -= 0.1 ; 
        	affichage_bg_animation(bg1,bg2,bg3,monitor ,xu2 ,xb2, &a2) ; 
        	afficher_image(front,monitor ,x2,290) ; 
        	}
        }
        
	*/
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

