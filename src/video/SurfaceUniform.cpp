/**
 * 	@file SurfaceUniform.cpp
 * 	@brief Implementation de la classe SurfaceUniform
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "SurfaceUniform.h"
#include "../util/debug.h"
#include "../video/Camera.h"
#include "../video/GraphicEngine.h"
#include "../util/globals.h"

#include "../../lib/SDL/include/SDL/SDL.h"

SurfaceUniform::SurfaceUniform(int width, int height, int r, int g, int b)
{
	m_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
    SDL_FillRect(m_surface,NULL,SDL_MapRGB(gGraphics->get_camera()->sdl_screen()->format,r,g,b));
}

SurfaceUniform::~SurfaceUniform()
{
	SDL_FreeSurface(m_surface);
}
