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
#include "video/PicturesContainer.h"

SurfaceText::SurfaceText()
{
	m_stringSurface = NULL;
}

SurfaceText::SurfaceText(std::string text, int size, int r, int g, int b, std::string font_name)
{
	init(text, size, r, g, b, font_name);
}

SurfaceText::~SurfaceText()
{
}

void SurfaceText::init(std::string text, int size, int r, int g, int b, std::string font_name)
{
	m_stringSurface = PicturesContainer::GetInstance()->loadSurfaceText(text, size, r, g, b, font_name);
	setSurface(m_stringSurface);
}

int SurfaceText::w() 
{
	return m_stringSurface? m_stringSurface->GetRect().GetWidth() : 5;
}

int SurfaceText::h()
{
	return m_stringSurface? m_stringSurface->GetRect().GetHeight() : 5;
	
}
