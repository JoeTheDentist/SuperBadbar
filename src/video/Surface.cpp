/**
 * 	@file surface.cpp
 * 	@brief Implémentation de la classe Surface
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <cmath>

#include "Surface.h"
#include "video/PicturesContainer.h"
#include "util/debug.h"

Surface::Surface (std::string filename)
{
    m_drawable = NULL;
    PRINT_CONSTR (3, "Construction d'une classe Surface");
    m_sprite = PicturesContainer::GetInstance()->load_picture (filename);
    setSurface (m_sprite);
    if ( !m_drawable )
    {
        PRINT_CONSTR (1, "Impossible de charger l'image : %s", filename.c_str() );
    }
}

Surface::Surface (sf::Sprite *sprite)
{
    m_drawable = NULL;
    PRINT_CONSTR (3, "Construction d'une classe Surface");
    m_sprite = sprite;
    setSurface (m_sprite);
    if ( !m_drawable )
    {
        PRINT_CONSTR (1, "Impossible de charger l'image depuis un sprite");
    }
}

Surface::~Surface()
{
    PRINT_CONSTR (3, "Destruction d'une classe Surface");
}

sf::Drawable *Surface::getSurface()
{
    return m_drawable;
}

sf::Sprite *Surface::getSprite()
{
    return m_sprite;
}

int Surface::w()
{
    return m_sprite ? m_sprite->GetSize().x : 5;
}

int Surface::h()
{
    return m_sprite ? m_sprite->GetSize().y : 5;

}

void Surface::set_w (int w)
{
}

void Surface::set_h (int h)
{
}


void Surface::blit_surface (Surface *background, Rect pos)
{
    //~ 	SDL_Rect *sdl_pos = new SDL_Rect;
    //~ 	sdl_pos->x = pos.x;
    //~ 	sdl_pos->y = pos.y;
    //~ 	SDL_BlitSurface(this->get_surface(), NULL, background->get_surface(), sdl_pos);
    //~ 	delete sdl_pos;
}

void Surface::blit_surface (Surface *background, Rect pos, Rect rel_pos)
{
    //~ 	SDL_Rect *sdl_pos = new SDL_Rect;
    //~ 	SDL_Rect *sdl_rel_pos = new SDL_Rect;
    //~ 	sdl_pos->x = pos.x;
    //~ 	sdl_pos->y = pos.y;
    //~ 	sdl_rel_pos->x = rel_pos.x;
    //~ 	sdl_rel_pos->y = rel_pos.y;
    //~ 	sdl_rel_pos->w = rel_pos.w;
    //~ 	sdl_rel_pos->h = rel_pos.h;
    //~ 	SDL_BlitSurface(this->get_surface(), sdl_rel_pos, background->get_surface(), sdl_pos);
    //~ 	delete sdl_pos;
    //~ 	delete sdl_rel_pos;
}

