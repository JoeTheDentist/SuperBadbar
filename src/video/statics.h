/**
 * Classe Static: donnée d'une image et de sa position



**/

#ifndef STATICS_H_INCLUDED
#define STATICS_H_INCLUDED

#include <SDL/SDL.h>
#include "../util/globals.h"

class Static
{
    private :
        SDL_Surface *m_image;
        Rect m_pos;

    public :
        Static();               /* Constructeurs */
        Static(std::string dir_image, Rect pos);
        Static(char *dir_image, uint32_t x, uint32_t y);
        ~Static();              /* Destructeur */
        SDL_Surface * image();  /* Accesseurs */
        Rect position();
};

#endif // STATICS_H_INCLUDED
