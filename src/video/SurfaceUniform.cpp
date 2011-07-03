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
#include "../video/TexturesManager.h"
#include "../video/Texture.h"
#include "../../lib/SDL/include/SDL/SDL.h"

SurfaceUniform::SurfaceUniform(int width, int height, int r, int g, int b)
{
	#ifndef _OPENGL_ACTIVE_
	setSurface(SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0));
    SDL_FillRect(get_surface(),NULL,SDL_MapRGB(gGraphics->get_camera()->sdl_screen()->format,r,g,b));
	#else
	setTexture(m_texturesManager->loadUniformSurface(width, height, r, g, b));
	#endif
}

SurfaceUniform::~SurfaceUniform()
{
	#ifndef _OPENGL_ACTIVE_
	SDL_FreeSurface(m_surface);
	#else
	delete getTexture();
	#endif
}
