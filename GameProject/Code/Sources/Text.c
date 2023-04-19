#include "../Headers/Text.h"
#include "../Headers/global.h"


Text* Text_Create(char *TEXT, char* FONT_NAME, SDL_Color color, int police){
    /* VARIABLES */
        Text* txt = (Text*)allocate(sizeof(Text));

    // Get the text from the parameter above:
    txt->text = TEXT;
    // Set the police:
    txt->police = police;
    // Make the font:
    txt->font = TTF_OpenFont(FONT_NAME, txt->police);
    // Get the color from the parameter above:
    txt->color = color;
    // Create the surface of the text:
    txt->surface = TTF_RenderText_Blended(txt->font, txt->text, txt->color);

    // Add the font to the pile of fonts to get executed at the end of the program:
    add_to_surface_pile(txt->surface);
    add_to_font_pile(txt->font);

    return txt;
}