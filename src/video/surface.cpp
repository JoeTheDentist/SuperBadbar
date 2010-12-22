/**
 * 	@file surface.cpp
 * 	@brief Implémentation de la classe Surface
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */
 
 
#include <iostream>
#include <SDL/SDL.h>
#include "surface.h"
#include "../video/pictures_container.h"
#include "../util/debug.h"

Pictures_container *Surface::m_pictures_container = NULL;



Surface::Surface(std::string filename)
{
	PRINT_CONSTR(3, "Construction d'une classe Surface");
	m_surface = m_pictures_container->load_BMP(filename);
}

Surface::~Surface()
{
	PRINT_CONSTR(3, "Destruction d'une classe Surface");
}

SDL_Surface * Surface::get_surface()
{
	return m_surface;
}

void Surface::set_pictures_container(Pictures_container *pictures_container)
{
	m_pictures_container = pictures_container;
	PRINT_DEBUG(1,"SEEEEEEEEET");
}

int Surface::w()
{
	return m_surface->w;
}

int Surface::h()
{
	return m_surface->h;
}

