/**
 * 	@file SurfaceText.cpp
 * 	@brief Implémentation de la classe SurfaceText
 *
 * 	@author Guillaume Berard & Benoit Morel
 * 	@date mars 2011
 *
 */

#include "SurfaceText.h"

#include <iostream>

#include "util/utils.h"
#include <video/Font.h>
#include <video/PicturesContainer.h>
#include <video/TexturesManager.h>

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
}

void SurfaceText::init(std::string text, int size, int r, int g, int b, std::string font_name)
{
	#ifdef _OPENGL_ACTIVE_
	setTexture(m_texturesManager->loadTextureText(text, size, r, g, b, font_name));
	#else
	setSurface(m_pictures_container->loadSurfaceText(text, size, r, g, b, font_name));
	#endif
}
