#include <iostream>
#include <stdint.h>
#include <string>

#include "statics.h"

Static::Static()
{
    m_image = NULL;
}

Static::Static(std::string dir_image, SDL_Rect pos)
{
    m_image = SDL_LoadBMP(dir_image.c_str());
    SDL_SetColorKey(m_image, SDL_SRCCOLORKEY, SDL_MapRGB(m_image->format, 0, 0, 255));
    m_pos = pos;
}

Static::Static(char *dir_image, uint32_t x, uint32_t y)
{
    m_image = SDL_LoadBMP(dir_image);
    m_pos.x = x;
    m_pos.y = y;
}

Static::~Static()
{
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
