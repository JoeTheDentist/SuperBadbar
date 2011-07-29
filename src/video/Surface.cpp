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

#include "../../lib/SDL/include/SDL/SDL.h"

#include "Surface.h"
#include "../video/PicturesContainer.h"
#include "../util/debug.h"

PicturesContainer *Surface::m_pictures_container = NULL;
#ifdef _OPENGL_ACTIVE_
#include "../video/TexturesManager.h"
#include "../video/Texture.h"
TexturesManager *Surface::m_texturesManager = NULL;
#endif


Surface::Surface(std::string filename)
{
	PRINT_CONSTR(3, "Construction d'une classe Surface");
	m_surface = m_pictures_container->load_IMG(filename);
	#ifdef _OPENGL_ACTIVE_
	m_texture = m_texturesManager->load_IMG(filename);
	#endif
	if ( !m_surface ) {
        PRINT_CONSTR(1, "Impossible de charger l'image : %s", filename.c_str());
	}

}

Surface::~Surface()
{
	/*
		NE PAS DELETER m_surface !! Ce pointeur est partage
		et sera PARFOIS deleted par le gestionnaire de surfaces
		selon le type de surface
	*/
	PRINT_CONSTR(3, "Destruction d'une classe Surface");
}

SDL_Surface * Surface::get_surface()
{
	return m_surface;
}

SDL_Surface *Surface::get_copy_surface()
{
   return SDL_ConvertSurface(m_surface, m_surface->format, m_surface->flags);
}

void Surface::set_pictures_container(PicturesContainer *picturesContainer)
{
	m_pictures_container = picturesContainer;
	PRINT_TRACE(1,"Ajout du PicturesContainer aux surfaces");
}
#ifdef _OPENGL_ACTIVE_
void Surface::setTexturesManager(TexturesManager *texturesManager)
{
	m_texturesManager = texturesManager;
	PRINT_TRACE(1,"Ajout du texturesManager aux surfaces");
}
#endif

int Surface::w()
{
	#ifdef _OPENGL_ACTIVE_
	return getTexture()->w();
	#else
	return m_surface->w;
	#endif
}

int Surface::h()
{
	#ifdef _OPENGL_ACTIVE_
	return getTexture()->h();
	#else
	return m_surface->h;
	#endif
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
	#ifndef _OPENGL_ACTIVE_
	SDL_SetAlpha(get_surface(), SDL_SRCALPHA, alpha);
	#else
	
	#endif
}
