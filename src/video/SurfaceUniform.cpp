/**
 * 	@file SurfaceUniform.cpp
 * 	@brief Implementation de la classe SurfaceUniform
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "SurfaceUniform.h"

#include <util/debug.h>
#include <util/globals.h>
#include <video/Camera.h>
#include <video/GraphicEngine.h>
#include <video/PicturesContainer.h>
#include <video/Texture.h>
#include <video/TexturesManager.h>

SurfaceUniform::SurfaceUniform(int width, int height, int r, int g, int b, int alpha)
{
	#ifndef _OPENGL_ACTIVE_
	setSurface(m_pictures_container->loadSurfaceUniform(width, height, r, g, b, alpha));
	#else
	setTexture(m_texturesManager->loadUniformSurface(width, height, r, g, b, alpha));
	#endif
	set_alpha(alpha);
}

SurfaceUniform::~SurfaceUniform()
{
	#ifndef _OPENGL_ACTIVE_
	#else
	delete getTexture();
	#endif
}
