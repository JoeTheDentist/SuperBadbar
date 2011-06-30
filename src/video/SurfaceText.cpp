/**
 * 	@file SurfaceText.cpp
 * 	@brief Implémentation de la classe SurfaceText
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "SurfaceText.h"
#include "../util/repertories.h"
#include "../util/debug.h"
#include "../video/Font.h"
#include <iostream>

#include "../../lib/SDL/include/SDL/SDL.h"
#include "../video/PicturesContainer.h"
#include "../video/TexturesManager.h"
SurfaceText::SurfaceText()
{

}

SurfaceText::SurfaceText(std::string text, int size, int r, int g, int b, std::string font_name)
{
	init(text, size, r, g, b, font_name);
}

SurfaceText::SurfaceText(std::string text, Font &font)
{
	m_surface = TTF_RenderText_Blended(font.get_TTF_font(), text.c_str(), font.get_color());
}

SurfaceText::~SurfaceText()
{
	// ON NE DELETE PAS, C'EST PICTURESCONTAINER QUI GERE LA MEMOIRE SDL
}

void SurfaceText::init(std::string text, int size, int r, int g, int b, std::string font_name)
{
	#ifdef _OPENGL_ACTIVE_
	setTexture(m_texturesManager->loadTextureText(text, size, r, g, b, font_name));
	#else	
	setSurface(m_pictures_container->loadSurfaceText(text, size, r, g, b, font_name));
	#endif
}
