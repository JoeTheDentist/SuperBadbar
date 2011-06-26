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
#include "../../lib/SDL/include/SDL/SDL_ttf.h"

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
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

void SurfaceText::init(std::string text, int size, int r, int g, int b, std::string font_name)
{
	TTF_Font *font = TTF_OpenFont((FONTS_R + font_name).c_str(), size);
	SDL_Color font_color;
	font_color.r = r;
	font_color.g = g;
	font_color.b = b;
	m_surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
	if (!m_surface)
		PRINT_DEBUG(1, "Erreur dans le chargement d'une surface texte");
	TTF_CloseFont(font);
}
