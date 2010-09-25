/**
 * Classe Static: donnée d'une image et de sa position



**/

#ifndef STATICS_H_INCLUDED
#define STATICS_H_INCLUDED

#include <SDL/SDL.h>

class Static
{
    private :
        SDL_Surface *m_image;
        SDL_Rect m_pos;

    public :
        Static();               /* Constructeurs */
        Static(std::string dir_image, SDL_Rect pos);
        Static(char *dir_image, uint32_t x, uint32_t y);
        ~Static();              /* Destructeur */
        SDL_Surface * image();  /* Accesseurs */
        SDL_Rect position();
};

#endif // STATICS_H_INCLUDED
