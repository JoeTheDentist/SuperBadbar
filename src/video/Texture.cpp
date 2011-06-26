/**
 * 	@file surface.cpp
 * 	@brief Implémentation de la classe Surface
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date decembre 2010
 *
 */

#include "../util/debug.h"
#ifdef _OPENGL_ACTIVE_

#include <iostream>
#include <cmath>

#include "../../lib/SDL/include/SDL/SDL.h"

#include "Texture.h"
#include "../video/TexturesManager.h"


Texture::Texture(GLuint texture, int w, int h) :
	m_texture(texture),
	m_w(w),
	m_h(h)
{
	
}

GLuint Texture::getGlTexture() const
{
	return m_texture;
}

int Texture::w() const
{
	return m_w;
}


int Texture::h() const
{
	return m_h;
}

#endif //#idef _OPENGL_ACTIVE_

