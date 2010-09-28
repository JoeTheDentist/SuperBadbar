#include <iostream>
#include <stdint.h>
#include <string>

#include "statics.h"
#include "../util/debug.h"

Static::Static()
{
	PRINT_CONSTR(3, "Construction d'un Static")
    m_image = NULL;
}

Static::Static(std::string dir_image, SDL_Rect pos)
{
	PRINT_CONSTR(3, "Construction du Static %s", dir_image.c_str())
    m_image = SDL_LoadBMP(dir_image.c_str());
    SDL_SetColorKey(m_image, SDL_SRCCOLORKEY, SDL_MapRGB(m_image->format, 0, 0, 255));
    m_pos = pos;
}

Static::Static(char *dir_image, uint32_t x, uint32_t y)
{
	PRINT_CONSTR(3, "Construction du Static %s", dir_image)
    m_image = SDL_LoadBMP(dir_image);
    m_pos.x = x;
    m_pos.y = y;
}

Static::~Static()
{
	PRINT_CONSTR(3, "Destruction d'un Static")
    SDL_FreeSurface(m_image);
}

SDL_Surface * Static::image()
{
    return m_image;
}

SDL_Rect Static::position()
{
    return m_pos;
}
