/**
 * 	@file surface_uniform.cpp
 * 	@brief Implementation de la classe Surface_uniform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "surface_uniform.h"
#include "../util/debug.h"
#include "../video/camera.h"
#include "../video/graphic_engine.h"
#include "../util/globals.h"

#include "../../lib/SDL/include/SDL/SDL.h"

Surface_uniform::Surface_uniform(int width, int height, int r, int g, int b)
{
	m_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
    SDL_FillRect(m_surface,NULL,SDL_MapRGB(gGraphics->get_camera()->sdl_screen()->format,r,g,b));
}

Surface_uniform::~Surface_uniform()
{

}
