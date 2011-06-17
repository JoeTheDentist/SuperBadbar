/**
 * 	@file surface.cpp
 * 	@brief Implémentation de la classe Surface
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */


#include <iostream>
#include <cmath>

#include "../../lib/SDL/include/SDL/SDL.h"

#include "surface.h"
#include "../video/pictures_container.h"
#include "../util/debug.h"

Pictures_container *Surface::m_pictures_container = NULL;

int norm_2(const Rect rect1, const Rect rect2)
{
	return (rect1 - rect2) * (rect1 - rect2);
}

int det(const Rect rect1, const Rect rect2)
{
	return rect1.x * rect2.y - rect2.x * rect1.y;
}

Rect operator+ (const Rect &rect1, const Rect &rect2)
{
	Rect res = rect1;
	res.x += rect2.x;
	res.y += rect2.y;
	return res;
}

Rect operator- (const Rect &rect1, const Rect &rect2)
{
	Rect res = rect1;
	res.x -= rect2.x;
	res.y -= rect2.y;
	return res;
}

int operator* (const Rect &rect1, const Rect &rect2)
{
	return rect1.x * rect2.x + rect1.y * rect2.y;
}

Surface::Surface(std::string filename)
{
	PRINT_CONSTR(3, "Construction d'une classe Surface");
	m_surface = m_pictures_container->load_IMG(filename);

}

Surface::Surface(Surface * s)
{
	PRINT_CONSTR(3, "Construction d'une classe Surface");
	m_surface = s->get_surface();
}

Surface::~Surface()
{
	/*
		NE PAS DELETER m_surface !! Ce pointeur est partage
		et sera deleted par le gestionnaire de surfaces
	*/
	PRINT_CONSTR(3, "Destruction d'une classe Surface");
}

SDL_Surface * Surface::get_surface()
{
	return m_surface;
}

void Surface::set_pictures_container(Pictures_container *pictures_container)
{
	m_pictures_container = pictures_container;
	PRINT_TRACE(1,"Ajout du Pictures_container aux surfaces");
}

int Surface::w()
{
	return m_surface->w;
}

int Surface::h()
{
	return m_surface->h;
}

void Surface::set_w(int w)
{
    m_surface->w = w;
}

void Surface::set_h(int h)
{
    m_surface->h = h;
}

void Surface::blit_surface(Surface *background, Rect pos, Rect rel_pos)
{
	SDL_Rect *sdl_pos = new SDL_Rect;
	SDL_Rect *sdl_rel_pos = new SDL_Rect;
	sdl_pos->x = pos.x;
	sdl_pos->y = pos.y;
	sdl_rel_pos->x = rel_pos.x;
	sdl_rel_pos->y = rel_pos.y;
	sdl_rel_pos->w = rel_pos.w;
	sdl_rel_pos->h = rel_pos.h;
	SDL_BlitSurface(this->get_surface(), sdl_rel_pos, background->get_surface(), sdl_pos);
	delete sdl_pos;
	delete sdl_rel_pos;
}

void Surface::blit_surface(Surface *background, Rect pos)
{
	SDL_Rect *sdl_pos = new SDL_Rect;
	sdl_pos->x = pos.x;
	sdl_pos->y = pos.y;
	SDL_BlitSurface(this->get_surface(), NULL, background->get_surface(), sdl_pos);
	delete sdl_pos;
}

void Surface::set_alpha(unsigned char alpha)
{
	SDL_SetAlpha(get_surface(), SDL_SRCALPHA, alpha);
}
