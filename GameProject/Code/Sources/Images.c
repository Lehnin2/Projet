#include "../Headers/Images.h"
#include "../Headers/global.h"

short bmp_image(char* filename){
    int i=strlen(filename)-1 , j=0;
    while(filename[i]!='.' && i)
        i--;
    i++;
    char ext[5];
    do{
        ext[j] = filename[i];
        j++;
        i++;
    }while(i<strlen(filename));
    ext[j] = 0;

    if (strcmp(ext,"bmp"))
        return 0;
    return 1;

}

Image* load_image(char* filename){
    /* VARIABLES */
        Image* img = (Image*)allocate(sizeof(Image));

    // Load the image:
    if (!bmp_image(filename))
        img->surface = IMG_Load(filename);
    else
        img->surface = SDL_LoadBMP(filename);

    // Check if the file loaded successfully:
    if (!img->surface)
        printf("\"%s\" NOT LOADED!\n", filename);

    // Set the image initial position:
    img->position.x = 0; img->position.y = 0;
    img->position.w = img->surface->w;
    img->position.h = img->surface->h;

    // Add the image to the queue of destruction:
    add_to_surface_pile(img->surface);

    return img;
}